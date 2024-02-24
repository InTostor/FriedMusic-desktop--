#pragma once
#include <cpr/cpr.h>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Data.hpp"
#include "SQLiteCpp/SQLiteCpp.h"
#include "StandartGlobalUser.hpp"
#include "macro.hpp"
#include "nlohman/json.hpp"

using namespace std;
using json = nlohmann::ordered_json;

class Client : public StandartGlobalCaller {
 private:
  bool _authenticated;
  string _username;
  Types::StorageType databaseType;
  cpr::Cookies cookies;

 public:
  void authenticate(string username, string password) {
    string url = getConfigValue("apiUrl") + "/authenticate.php";
    cpr::Response response =
        cpr::Get(cpr::Url(url),
                 cpr::Authentication(username, password, cpr::AuthMode::BASIC));
    cookies = response.cookies;
    if (response.status_code == 200) {
      this->_authenticated = true;
      this->_username = username;
    } else {
      this->_authenticated = false;
      this->_username = "anonymous";
    }
    eventProcessor(Types::Event::AUTHENTICATION_TRYED);
  }
  string getUsername() { return _username; };
  bool isServerAccessible() {
    cpr::Response response = cpr::Head(cpr::Url(getConfigValue("apiUrl")));
    return response.status_code == 200;
  }
  bool isAuthenticated() { return _authenticated; };
  void downloadDatabase() {
    string url = getConfigValue("apiUrl") + "/selectMetadata.php?sql";
    cpr::Response dataResponse = cpr::Get(cpr::Url(url), cookies);

    if (dataResponse.status_code == 200) {
      url = getConfigValue("apiUrl") +
            "/getDatabaseCreateStatement.php?typesonly";
      // if API available, there is no sense to check it twice

      json values = json::parse(cpr::Get(cpr::Url(url), cookies).text);
      string sqlCreate =
          "CREATE TABLE `fullmeta` "
          "( `id` int NOT NULL,`filename` varchar(256) "
          "DEFAULT NULL,`title` varchar(256) DEFAULT NULL,"
          "`duration` int DEFAULT NULL,"
          "`album` varchar(256) DEFAULT NULL,"
          "`tracknumber` int DEFAULT NULL,"
          "`genre` varchar(45) NOT NULL,"
          "`artist` varchar(256) DEFAULT NULL,"
          "`year` int DEFAULT NULL,"
          "`filesize` int DEFAULT NULL) ";

      json data = json::parse(dataResponse.text);

      SQLite::Database db(getConfigValue("databasePath"),
                          SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

      db.exec("DROP TABLE IF EXISTS fullmeta");  // purge all data, because
                                                 // server is more authoritative
      db.exec(sqlCreate);

      string sqlInsert = "INSERT INTO `fullmeta` VALUES(";
      bool firstPass;
      // SQLite::Statement insertStatement;

      // generate sql
      for (json::iterator it = data.begin(); it != data.end(); ++it) {
        for (auto& [key, value] : it->items()) {
          if (!firstPass) {
            sqlInsert += "?,";
          } else {
          }
        }
        sqlInsert.pop_back();
        if (!firstPass) {
          sqlInsert += ")";
          firstPass = true;
          break;
        }
      }
      int valueIndex = 0;
      SQLite::Transaction transaction(db);
      for (json::iterator it = data.begin(); it != data.end(); ++it) {
        SQLite::Statement insertStatement(db, sqlInsert);
        valueIndex = 0;
        for (auto& [key, value] : it->items()) {
          valueIndex += 1;
          if (value.is_null()) {
            insertStatement.bind(valueIndex, "");
          } else if (value.is_string()) {
            insertStatement.bind(valueIndex, value.get<std::string>());
          } else if (value.is_number()) {
            insertStatement.bind(valueIndex, value.get<int>());
          }
        }
        insertStatement.executeStep();
      }
      transaction.commit();
    }
  }
  void pullRemote() {
    cpr::Response response = cpr::Get(
        cpr::Url(getConfigValue("apiUrl") + "/getMyPlaylists.php"), cookies);
    string filesList;
    if (response.status_code == 200) {
      filesList += response.text;
    }
    response = cpr::Get(
        cpr::Url(getConfigValue("apiUrl") + "/getMyBlocklists.php"), cookies);
    if (response.status_code == 200) {
      filesList += "\n";
      filesList += response.text;
    }

    istringstream lineStream(filesList);
    string filename;
    string username = getUsername();
    while (std::getline(lineStream, filename, '\n')) {
      if ((filename != "") and (filename != "\n")) {
        cout << "Downloading " << filename << endl;
        if (!filesystem::is_directory(
                getConfigValue("localUserdataStoragePath")) ||
            !filesystem::exists(getConfigValue("localUserdataStoragePath"))) {
          filesystem::create_directory(
              getConfigValue("localUserdataStoragePath"));
        }
        downloadFileAsync(
            getConfigValue("userdataStorageUrl") + "/" + username + "/" +
                filename,
            getConfigValue("localUserdataStoragePath") + "/" + filename);
      }
    }
  };
  void pushRemote() {
    for (filesystem::directory_entry const& dir_entry :
         filesystem::directory_iterator(
             getConfigValue("localUserdataStoragePath"))) {
      if (dir_entry.path() == "." || dir_entry.path() == ".." ||
          dir_entry.path() == "") {
        continue;
      }

      cout << "Uploading " << dir_entry << endl;
      cpr::Response response =
          cpr::Post(cpr::Url(getConfigValue("apiUrl") + "/uploadFile.php"),
                    cpr::Multipart{{"file", cpr::File(dir_entry.path())}});
    }
  };
  void downloadTrack(vector<string> filenames) {
    for (string filename : filenames) {
      downloadTrack(filename);
    }
  };
  void downloadTrack(string filename) {
    string url = getConfigValue("musicStorageUrl") + filename;
    string dest = getConfigValue("localMusicStoragePath") + "/" + filename;
    downloadFile(url, dest);
  };
  Client(){};
  vector<string> getTracksList(Types::StorageType where);
  vector<string> getPlaylistFiles(Types::StorageType where) {
    vector<string> temp;
    for (const auto& entry :
         filesystem::directory_iterator(getConfigValue(""))) {
      if (entry.path() == "." || entry.path() == ".." ||
          !(filesystem::path(entry.path()).extension() == ".fpl")) {
        continue;
      }
      temp.push_back(entry.path());
    }
    return temp;
  };
  vector<Source> getPlaylistsSource(Types::StorageType where);
  Source lookupTrack(string filename) {
    string localPath = getConfigValue("localMusicStoragePath") + filename;

    if (filesystem::exists(localPath)) {
      Source source(localPath, Types::StorageType::LOCAL,
                    Types::PathType::FILESYSTEMPATH, Types::DataType::TRACK);
      return source;
    }
    string remoteUrl = getConfigValue("musicStorageUrl") + filename;

    cpr::Response response =
        cpr::Head(cpr::Url(ReplaceInString(remoteUrl, " ", "%20")));
    if (response.status_code == 200) {
      Source source(remoteUrl, Types::StorageType::REMOTE, Types::PathType::URL,
                    Types::DataType::TRACK);
      return source;
    }
    Source source;

    return source;
  }
  void assembleTrack(Track* track) {
    SQLite::Database db(getConfigValue("databasePath"));
    SQLite::Statement query(
        db,
        "SELECT title, album, tracknumber, genre, year, duration, artist "
        "FROM fullmeta WHERE filename = ?");
    query.bind(1, track->filename);
    while (query.executeStep()) {
      const char* title;
      const char* album;
      const char* genre;
      int albumTrackNumber;
      int year;
      int duration;
      const char* artists;
      title = query.getColumn(0);
      album = query.getColumn(1);
      genre = query.getColumn(3);
      albumTrackNumber = query.getColumn(2);
      year = query.getColumn(4);
      duration = query.getColumn(5);
      artists = query.getColumn(6);
      track->title = title;
      track->album = album;
      track->albumTrackNumber = albumTrackNumber;
      track->genre = genre;
      track->year = year;
      track->duration = duration;
      track->artists = artists;
      track->isAssembled = true;
      break;
    }
  };
  // bad implementation. rewrite with single query
  void assembleTrack(vector<Track*> tracks) {
    for (int i = 0; i < tracks.size(); i++) {
      assembleTrack(tracks[i]);
    }
  };

  Playlist getPlaylistFromSource(Source source, bool assemble = false) {
    bool found = false;
    Playlist playlist;
    playlist.tracks = {};
    vector<string> searchList;

    playlist.name = filesystem::path(source.path).filename();

    if (source.pathType == Types::PathType::URL) {
      searchList.push_back(getConfigValue("userdataStorageUrl") +
                           getUsername() + "/" + source.path);
      cpr::Response response;
      for (string url : searchList) {
        response = cpr::Get(cpr::Url(url));
        if (response.status_code == 200) {
          found = true;
          break;
        }
      }
      if (found) {
        string filename;
        istringstream lineStream(response.text);
        while (std::getline(lineStream, filename, '\n')) {
          Track track;
          track.filename = filename;
          track.source = lookupTrack(filename);
          if (assemble) {
            assembleTrack(&track);
          }
          playlist.tracks.push_back(track);
        }
      }
    } else if (source.pathType == Types::PathType::FILESYSTEMPATH) {
      ifstream file(source.path);
      if (!file.is_open()) {
        Playlist playlist;
        return playlist;  // handle it somehow
      } else {
        string filename;
        while (std::getline(file, filename)) {
          Track track;
          track.filename = filename;
          track.source = lookupTrack(filename);
          if (assemble) {
            assembleTrack(&track);
          }
          playlist.tracks.push_back(track);
        }

        file.close();
      }

    } else {
      return Playlist();
    }
    return playlist;
  };
};
#include <cpr/cpr.h>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "lib/FriedMusic/Data.hpp"
#include "lib/FriedMusic/Library.hpp"
#include "SQLiteCpp/SQLiteCpp.h"
#include "lib/FriedMusic/StandartGlobalUser.hpp"
// #include "lib/FriedMusic/macro.hpp"
#include <nlohmann/json.hpp>
#include "lib/FriedMusic/Client.hpp"

using namespace std;
using json = nlohmann::ordered_json;

void Client::authenticate(string username, string password) {
  string url = getConfigValue("apiUrl") + "/authenticate.php";
  cpr::Response response =
      cpr::Get(cpr::Url(url),
               cpr::Authentication(username, password, cpr::AuthMode::BASIC),
               cpr::Timeout{3000});
  if (response.elapsed > 3000) {
    eventProcessor(Types::Event::API_CONNECTION_FAILED);
    return;
  }
  cookies = response.cookies;
  if (response.status_code == 200) {
    this->_authenticated = true;
    this->_username = username;
    eventProcessor(Types::Event::AUTHENTICATION_SUCCESS);
  } else {
    this->_authenticated = false;
    this->_username = "anonymous";
    eventProcessor(Types::Event::AUTHENTICATION_FAILED);
  }
  eventProcessor(Types::Event::AUTHENTICATION_TRYED);
}
string Client::getUsername() { return _username; };
bool Client::isServerAccessible() {
  cpr::Response response = cpr::Head(cpr::Url(getConfigValue("apiUrl")));
  return response.status_code == 200;
}
bool Client::isAuthenticated() { return _authenticated; };
void Client::downloadDatabase() {
  string url = getConfigValue("apiUrl") + "/selectMetadata.php?sql";
  cpr::Response dataResponse = cpr::Get(cpr::Url(url), cookies);

  if (dataResponse.status_code == 200) {
    url =
        getConfigValue("apiUrl") + "/getDatabaseCreateStatement.php?typesonly";
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
void Client::pullRemote() {
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
void Client::pushRemote() {
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
void Client::downloadTrack(vector<string> filenames) {
  for (string filename : filenames) {
    downloadTrack(filename);
  }
};
void Client::downloadTrack(string filename) {
  string url = getConfigValue("musicStorageUrl") + filename;
  string dest = getConfigValue("localMusicStoragePath") + "/" + filename;
  downloadFile(url, dest);
};
void Client::deleteTrack(string filename) {
  filesystem::remove(getConfigValue("localMusicStoragePath") + filename);
}
Client::Client(){};
// vector<string> Client::getTracksList(Types::StorageType where){};
vector<string> Client::getPlaylistFiles(Types::StorageType where) {
  vector<string> temp;
  for (const auto& entry : filesystem::directory_iterator(getConfigValue(""))) {
    if (entry.path() == "." || entry.path() == ".." ||
        !(filesystem::path(entry.path()).extension() == ".fpl")) {
      continue;
    }
    temp.push_back(entry.path());
  }
  return temp;
};
// vector<Source> Client::getPlaylistsSource(Types::StorageType where){};
Source Client::lookupTrack(string filename) {
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
void Client::assembleTrack(Track* track) {
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

vector<Track> Client::assembleTracks(vector<Track> tracks) {
  // bad implementation. rewrite with single query
  // for (int i = 0; i < tracks.size(); i++) {
  //   assembleTrack(tracks[i]);
  // }
  // Handle big lists with sql query size limit
  if (distance(tracks.begin(), tracks.end()) > 500) {
    vector<Track> left = sliceVector(tracks, 0, 499);
    vector<Track> right = sliceVector(tracks, 500, tracks.size() - 1);
    left = assembleTracks(left);
    right = assembleTracks(right);
    left.insert(left.end(), right.begin(), right.end());
    return left;
  }
  string sql =
      "SELECT title, album, tracknumber, genre, year, duration, artist, "
      "filename "
      "FROM fullmeta WHERE filename IN(";
  vector<string> zeros;
  vector<string> filenames;
  for (int i = 0; i < tracks.size(); i++) {
    zeros.push_back("?");
    filenames.push_back(tracks[i].filename);
  }
  sql += join(zeros, ",");
  sql += ")";
  SQLite::Database db(getConfigValue("databasePath"));

  SQLite::Statement query(db, sql);

  for (int i = 0; i < tracks.size(); i++) {
    query.bind(i + 1, tracks[i].filename);
  }
  int i = 0;
  while (query.executeStep()) {
    const char* filename;
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
    filename = query.getColumn(7);

    vector<Track>::iterator it =
        std::find_if(tracks.begin(), tracks.end(),
                     [&](Track const& t) { return t.filename == filename; });
    while (it != tracks.end()) {
      if ((*it).filename == filename) {
        int trackIndexFound = it - tracks.begin();
        tracks[trackIndexFound].title = title;
        tracks[trackIndexFound].album = album;
        tracks[trackIndexFound].albumTrackNumber = albumTrackNumber;
        tracks[trackIndexFound].genre = genre;
        tracks[trackIndexFound].year = year;
        tracks[trackIndexFound].duration = duration;
        tracks[trackIndexFound].artists = artists;
        tracks[trackIndexFound].isAssembled = true;
      }
      it++;
    }

    i++;
  }
  return tracks;
};

Playlist Client::getPlaylistFromSource(Source source, bool assemble) {
  bool found = false;
  Playlist playlist;
  playlist.tracks = {};
  vector<string> searchList;

  playlist.name = filesystem::path(source.path).filename();

  if (source.pathType == Types::PathType::URL) {
    searchList.push_back(getConfigValue("userdataStorageUrl") + getUsername() +
                         "/" + source.path);
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
        // if (assemble) {
        // assembleTrack(&track);
        // }
        playlist.tracks.push_back(track);
      }
      if (assemble) {
        playlist.tracks = assembleTracks(playlist.tracks);
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
        // if (assemble) {
        //   assembleTrack(&track);
        // }
        playlist.tracks.push_back(track);
      }
      if (assemble) {
        playlist.tracks = assembleTracks(playlist.tracks);
      }
      file.close();
    }

  } else {
    return Playlist();
  }
  return playlist;
};
bool Client::isTrackInPlaylist(Track track, Playlist playlist) {
  for (Track _track : playlist.tracks) {
    if (_track.filename == track.filename) {
      return true;
    }
  }
  return false;
}

bool Client::isTrackInPlaylist(Track track, Source source) {
  return isTrackInPlaylist(track, getPlaylistFromSource(source));
}

bool Client::isTrackDownloaded(Track track) {
  return std::filesystem::exists(
      getConfigValue("localMusicStoragePath") +
      string(filesystem::path(track.filename).filename()));
}
bool Client::isSourceExistsLocally(Source source) {
  return Library::isSourceExists(source) == Types::StorageType::LOCAL;
}

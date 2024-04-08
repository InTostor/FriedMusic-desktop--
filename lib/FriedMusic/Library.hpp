#pragma once
#include <cassert>
#include <iostream>
#include <string>

#include "Client.hpp"
#include "Data.hpp"
#include "SQLiteCpp/SQLiteCpp.h"
#include "StandartGlobalUser.hpp"
#include "globals.h"
#include "macro.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Library {
public:
  Library() = delete;

  /// @brief Finds source to the requested filename (user scope). prefers local
  /// @param filename basename of playlist (favourite.fpl)
  /// @param client pointer to global client object
  /// @return constructed source if found
  static inline Source getPlaylistSource(string filename) {
    Source favSource(getConfigValue("localUserdataStoragePath") + "/" +
                         filename,
                     Types::StorageType::LOCAL, Types::PathType::FILESYSTEMPATH,
                     Types::DataType::PLAYLIST);
    Types::StorageType existence = Library::isSourceExists(favSource);
    if (existence == Types::StorageType::LOCAL ||
        existence == Types::StorageType::ANY) {
      return favSource;
    }

    if (client.isAuthenticated()) {
      favSource = Source(getConfigValue("userdataStorageUrl") +
                             client.getUsername() + "/" + filename,
                         Types::StorageType::REMOTE, Types::PathType::URL,
                         Types::DataType::PLAYLIST);
    }
    return Source();
  }
  static inline Types::StorageType isSourceExists(Source source) {
    bool eLocal = false;
    bool eRemote = false;
    string path;
    string url;
    if (source.dataType == Types::DataType::TRACK) {
      path = getConfigValue("localMusicStoragePath") +
             string(filesystem::path(source.path).filename());
      url = getConfigValue("musicStorageUrl") +
            string(filesystem::path(source.path).filename());
    } else if (source.dataType == Types::DataType::PLAYLIST) {
      path = getConfigValue("localUserdataStoragePath") +
             string(filesystem::path(source.path).filename());
      url = getConfigValue("userdataStorageUrl") +
            string(filesystem::path(source.path).filename());
    }
    if (std::filesystem::exists(path)) {
      eLocal = true;
    }
    // if second is not enough, maybe there are problems with link or server. in
    // any case that's too long
    cpr::Response response = cpr::Head(cpr::Url(url), cpr::Timeout{1000});
    if (response.elapsed < 1000 and response.status_code == 200) {
      eRemote = true;
    }
    if (eLocal and eRemote) {
      return Types::StorageType::ANY;
    }
    if (eLocal) {
      return Types::StorageType::LOCAL;
    }
    if (eRemote) {
      return Types::StorageType::REMOTE;
    }
    return Types::StorageType::NONE;
  }

  static inline bool isTrackInPlaylist(Track track, Playlist playlist) {
    for (Track _track : playlist.tracks) {
      if (_track.filename == track.filename) {
        return true;
      }
    }
    return false;
  }

  static inline bool isTrackInPlaylist(Track track, Source source) {

    return isTrackInPlaylist(track, client.getPlaylistFromSource(source));

    return false;
  }

  static inline void deleteTrack(string filename) {
    filesystem::remove(getConfigValue("localMusicStoragePath") + filename);
  }
  static inline void deleteTrack(Track track) {
    filesystem::remove(getConfigValue("localMusicStoragePath") +
                       track.filename);
  }

  static inline void savePlaylistLocally(Playlist playlist) {
    ofstream file;
    string path = getConfigValue("localUserdataStoragePath") + playlist.name;
    file.open(path, ios::out);
    int i = 0;
    for (Track track : playlist.tracks) {
      if (track.filename.length() < 4) {
        continue;
      }
      file << track.filename;
      if (i < playlist.size()) {
        file << "\n";
      }
    }
    file.close();

    client.eventProcessor(Types::Event::FILES_UPDATED);
  }
  // Types::DataType detectDataType(string filename) {}

  struct fuzzySearchOutput {
    vector<Source> playlists;
    vector<Source> tracks;
    vector<string> artists;
  };

  static inline fuzzySearchOutput fuzzySearch(string query) {
    fuzzySearchOutput out;
    if (query.length() == 0) {
      return out;
    }

    SQLite::Database db(getConfigValue("databasePath"), SQLite::OPEN_READONLY);

    string sql;
    if (query.rfind("HTTP") == 0) {
      // detect type of url, return smth
    } else if (query.rfind("SQL") == 0) {
      sql = query;
      sql.erase(0, 4);
    } else {
      vector<string> tokens = explodeMultiplDelimeters(query, {" ", ";", "; "});

      sql = "SELECT filename, artist FROM fullmeta WHERE ";

      // artists, albums, filenames
      for (string token : tokens) {
        sql += "artist LIKE ? or filename LIKE ? or album LIKE "
               "? or title LIKE ?";
        if (token != tokens.back()) {
          sql += " or ";
        }
      }
      sql += " LIMIT 2000 ";
      SQLite::Statement query(db, sql);

      // bind
      int i = 1;
      for (string token : tokens) {
        query.bind(i, "%" + token + "%");
        query.bind(i + 1, "%" + token + "%");
        query.bind(i + 2, "%" + token + "%");
        query.bind(i + 3, "%" + token + "%");
        i += 4;
      }
      vector<string> tempArtists;
      vector<string> tempTrackFilename;

      while (query.executeStep()) {
        const char *currArtitst = query.getColumn(1);
        const char *currTrack = query.getColumn(0);

        if (std::find(tempArtists.begin(), tempArtists.end(), currArtitst) ==
            tempArtists.end()) {
          tempArtists.push_back(currArtitst);
        }
        tempTrackFilename.push_back(currTrack);
      }

      // set tracks
      out.artists = tempArtists;

      out.tracks = client.lookupTrack(tempTrackFilename);

      for (string token : tokens) {

        for (const auto &entry : filesystem::directory_iterator(
                 getConfigValue("localUserdataStoragePath"))) {
          if (string(entry.path()).find(token) != std::string::npos) {
            Source plSource = Source(entry.path(), Types::StorageType::LOCAL,
                                     Types::PathType::FILESYSTEMPATH,
                                     Types::DataType::PLAYLIST);
            out.playlists.push_back(plSource);
          }
        }
      }
    }
    return out;
  }
  static inline vector<Source> getLocalPlaylistSources() {
    string ext(".fpl");
    string path = getConfigValue("localUserdataStoragePath");
    vector<Source> sources;
    for (auto &p : filesystem::recursive_directory_iterator(path)) {
      if (p.path().extension() == ext) {
        sources.push_back(Source(p.path(), Types::StorageType::LOCAL,
                                 Types::PathType::FILESYSTEMPATH,
                                 Types::DataType::PLAYLIST));
      }
    }
    return sources;
  }
  static inline void addTrackToFilePlaylist(Track track,
                                            Source playlistSource) {
    if (playlistSource.storageType == Types::StorageType::LOCAL) {
      ofstream file;
      file.open(playlistSource.path, ios::out | ios::app | ios::binary);
      file << filesystem::path(track.source.path).filename().string() << endl;
      file.close();
      return;
    }
  }
};

class MainGeneratorPlaylist : public Playlist, public virtual DynamicPlaylistInterface {
public:
  std::string name = "dynamic";
  bool isDynamic = true;

  Track getNextTrack() {
    Track returnTrack;
    vector<string> references = {"history", "favourite", "database"};
    vector<float> referenceWeights = {10.0, 20.0, 1.0};
    vector<string> properties = {
        "self",
        "album",
        "artist",
        "genre",
    };
    vector<float> propertyWeights = {2.0, 10.0, 20.0, 10.0};
    // string referenceDecision = randomByWeight(references, referenceWeights);
    string referenceDecision = "favourite";
    cout << "ref" << referenceDecision << endl;

    // Switch may look good, but it does not allow of this style variable
    // declaration
    Track referenceTrack;
    if (referenceDecision == "history") {
      Playlist historyPlaylist = client.getPlaylistFromSource(
          Library::getPlaylistSource("history.fpl"), false);
      int random_number = rand() % historyPlaylist.size() - 1;
      referenceTrack = historyPlaylist.tracks[random_number];
    }
    if (referenceDecision == "favourite") {
      Playlist favouritePlaylist = client.getPlaylistFromSource(
          Library::getPlaylistSource("favourite.fpl"), false);
      int random_number = rand() % favouritePlaylist.size() - 1;
      referenceTrack = favouritePlaylist.tracks[random_number];
    }
    referenceTrack = client.assembleTrack(referenceTrack);
    

    if (referenceDecision == "database") {
      string sql = "SELECT filename from fullmeta ORDER BY RANDOM() LIMIT 1";
      SQLite::Database db(getConfigValue("databasePath"),
                          SQLite::OPEN_READONLY);
      SQLite::Statement query(db, sql);
      while (query.executeStep()) {
        returnTrack.source = client.lookupTrack(query.getColumn(0));
        returnTrack = client.assembleTrack(returnTrack);

        return returnTrack;
      }
    }

    // string propertyDecision = randomByWeight(properties, propertyWeights);
    string propertyDecision = "genre";
    cout << "prop" << referenceDecision << endl;
    if (propertyDecision == "self") {
      returnTrack = referenceTrack;
      return referenceTrack;
    }
    SQLite::Database db(getConfigValue("databasePath"), SQLite::OPEN_READONLY);

    if (propertyDecision == "album") {
      string sql = "SELECT filename from fullmeta WHERE album = ? ORDER BY "
                   "RANDOM() LIMIT 1";
      SQLite::Statement query(db, sql);
      query.bind(1, referenceTrack.album);
      while (query.executeStep()) {
        returnTrack = client.lookupTrack(query.getColumn(0));
        break;
      }
    } else if (propertyDecision == "artist") {
      string sql = "SELECT filename from fullmeta WHERE artist in (";
      string sqlPlaces;
      vector<string> splitArtists = referenceTrack.getSplitArtists();
      for (int i = 0; i <= splitArtists.size() - 1; i++) {
        sqlPlaces += "?";
        if (i != splitArtists.size() - 1) {
          sqlPlaces += ",";
        }
      }
      sql += sqlPlaces;
      sql += ") ORDER BY RANDOM() LIMIT 1";
      SQLite::Statement query(db, sql);
      for (int i = 1; i <= splitArtists.size(); i++) {
        query.bind(i, splitArtists[i - 1]);
      }
      while (query.executeStep()) {
        returnTrack = client.lookupTrack(query.getColumn(0));
        break;
      }
    } else {
      // (propertyDecision == "genre")
      string sql = "SELECT filename from fullmeta WHERE genre = ? ORDER BY "
                   "RANDOM() LIMIT 1";
      SQLite::Statement query(db, sql);
      query.bind(1, referenceTrack.genre);
      while (query.executeStep()) {
        returnTrack = client.lookupTrack(query.getColumn(0));
        break;
      }
    }

    return returnTrack;
  };
};
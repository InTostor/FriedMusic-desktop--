#pragma once
#include <iostream>
#include <string>

#include "Client.hpp"
#include "Data.hpp"
#include "StandartGlobalUser.hpp"
#include "macro.hpp"
#include <filesystem>
#include <fstream>

using namespace std;

class Library {
public:
  Library() = delete;

  /// @brief Finds source to the requested filename (user scope). prefers local
  /// @param filename basename of playlist (favourite.fpl)
  /// @param client pointer to global client object
  /// @return constructed source if found
  static inline Source getPlaylistSource(string filename,
                                         Client *client = nullptr) {
    Source favSource(getConfigValue("localUserdataStoragePath") + "/" +
                         filename,
                     Types::StorageType::LOCAL, Types::PathType::FILESYSTEMPATH,
                     Types::DataType::PLAYLIST);
    Types::StorageType existence = Library::isSourceExists(favSource);
    if (existence == Types::StorageType::LOCAL ||
        existence == Types::StorageType::ANY) {
      return favSource;
    }
    if (!client) {
      return Source();
    } // no client
    if (client->isAuthenticated()) {
      favSource = Source(getConfigValue("userdataStorageUrl") +
                             client->getUsername() + "/" + filename,
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

  static inline bool isTrackInPlaylist(Track track, Source source,
                                       Client *client = nullptr) {
    if (client) {
      return isTrackInPlaylist(track, client->getPlaylistFromSource(source));
    }
    return false;
  }

  static inline void deleteTrack(string filename) {
    filesystem::remove(getConfigValue("localMusicStoragePath") + filename);
  }
  static inline void deleteTrack(Track track) {
    filesystem::remove(getConfigValue("localMusicStoragePath") +
                       track.filename);
  }

  static inline void savePlaylistLocally(Playlist playlist, StandartGlobalCaller *eventEmitter = nullptr) {
    ofstream file;
    string path = getConfigValue("localUserdataStoragePath") + playlist.name;
    file.open(path, ios::out);
    int i = 0;
    for (Track track : playlist.tracks) {
      file << track.filename;
      if (i < playlist.size()) {
        file << "\n";
      }
    }
    file.close();
    if (eventEmitter != nullptr){
      eventEmitter->eventProcessor(Types::Event::FILES_UPDATED);
    }
  }

  // struct fuzzySearchOutput {
  // vector<Playlist> playlists;
  // vector<Track> tracks;
  // vector<string> artists;
  // };
  // fuzzySearchOutput fuzzySearch() {}
};

#include <iostream>
#include <string>
#include <vector>

#include "Data.hpp"
#include <cpr/cpr.h>
#include "macro.hpp"
#pragma once
using namespace std;

class Client {
 private:
  bool _authenticated;
  std::string _username;
  Types::StorageType databaseType;

 public:
  void authenticate();
  std::string getUsername() { return _username; };
  void registerListener();  // use class listener
  bool isServerAccessible();
  bool isAuthenticated();
  void downloadDatabase();
  void pullRemote();
  void pushRemote();
  void downloadTrack(vector<std::string> filenames);
  void downloadTrack(std::string filename){
    std::string url = getConfigValue("musicStorageUrl") + filename;
    cpr::Response response = cpr::get(url);
    if (response.status_code == 200){

    }
  };
  Client();
  vector<std::string> getTracksList(Types::StorageType where);
  vector<std::string> getPlaylistFiles(Types::StorageType where);
  vector<Source> getPlaylistsSource(Types::StorageType where);
  Source lookupTrack(std::string filename) {
    std::string localPath = getConfigValue("localMusicStorage");
    if (filesystem::exists(localPath)) {
      Source source(localPath, Types::StorageType::LOCAL,
                    Types::PathType::FILESYSTEMPATH, Types::DataType::TRACK);
      return source;
    }

    std::string remoteUrl = getConfigValue("musicStorageUrl") + filename;
    cpr::Response response = cpr::Head(cpr::Url(remoteUrl));
    if (response.status_code == 200) {
      Source source(remoteUrl, Types::StorageType::REMOTE, Types::PathType::URL,
                    Types::DataType::TRACK);
      return source;
    }
    Source source;
    return source;
  }
  void assembleTrack(Track *track);
  void assembleTrack(vector<reference_wrapper<Track>> tracks) {
    vector<std::string> originalFilenames;
    std::string sql;

    for (int i = 0; i < tracks.size(); i++) {
      originalFilenames.insert(originalFilenames.begin() + i,
                               filesystem::path(tracks[i].get().filename));
    }
    if (databaseType == Types::StorageType::LOCAL) {
      sql.append(" SELECT * FROM fullmeta WHERE filename in (");
      sql.append(join(originalFilenames, ","));
      sql.append(")");
    } else {
      sql.append("WHERE filename IN (");
      sql.append(join(originalFilenames, ","));
      sql.append(")");
    }
  };

  Playlist getPlaylistFromSource(Source source, bool assemble = false);
};
#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "macro.hpp"
using namespace std;

namespace Types {
enum class StorageType { LOCAL, REMOTE, ANY, NONE };
enum class PathType { URL, FILESYSTEMPATH, ANY, NONE };
enum class DataType {
  DATA,
  TRACK,
  PLAYLIST,
  BLOCKLIST,
  ALBUM,
  ARTISTSTRACKS,
  LOCALDATABASE,
  ANY,
  NONE
};
enum Loop { NONE, TRACKONCE, TRACK, PLAYLISTONCE, PLAYLIST };
// most types are VLC names, even when QT used
enum Event {
  unknown,
  AUTHENTICATION_TRYED,
  AUTHENTICATION_SUCCESS,
  AUTHENTICATION_FAILED,
  DATABASE_LOAD_FAILED,
  API_CONNECTION_FAILED,
  STORAGE_CONNECTION_FAILED,
  FILES_UPDATED,
  SOUNDMAKER_PLAYLIST_SET,
  onMediaPlayerLoopModeChanged,
  onMediaPlayerMediaChanged,
  onMediaPlayerNothingSpecial,
  onMediaPlayerOpening,
  onMediaPlayerOpened,
  onMediaPlayerBuffering,
  onMediaPlayerBuffered,
  onMediaPlayerPlaying,
  onMediaPlayerPaused,
  onMediaPlayerStopped,
  onMediaPlayerMediaFinished,
  onMediaPlayerForward,
  onMediaPlayerBackward,
  onMediaPlayerEncounteredError,
  onMediaPlayerTimeChanged,
  onMediaPlayerPositionChanged,
  onMediaPlayerLengthChanged,
  onMediaPlayerVout,
  onMediaPlayerESAdded,
  onMediaPlayerESDeleted,
  onMediaPlayerESSelected,
  onMediaPlayerCorked,
  onMediaPlayerUncorked,
  onMediaPlayerMuted,
  onMediaPlayerUnmuted,
  onMediaPlayerAudioVolume,
  onMediaPlayerAudioDevice
};
};  // namespace Types

class Source {
 public:
  std::string path;
  Types::StorageType storageType;
  Types::PathType pathType;
  Types::DataType dataType;
  Source(std::string setpath, Types::StorageType setstorageType,
         Types::PathType setpathType, Types::DataType setdataType) {
    path = setpath;
    storageType = setstorageType;
    pathType = setpathType;
    dataType = setdataType;
  }
  Source(std::string setpath) {
    path = setpath;
    storageType = Types::StorageType::ANY;
    pathType = Types::PathType::ANY;
    dataType = Types::DataType::ANY;
  }
  Source() {
    path = "";
    storageType = Types::StorageType::NONE;
    pathType = Types::PathType::NONE;
    dataType = Types::DataType::NONE;
  }
  std::string getUrlEncodedPath() {
    if (pathType == Types::PathType::URL) {
      std::string out = path;
      out = ReplaceInString(out, "&", "%26");
      out = ReplaceInString(out, " ", "%20");
      return out;
    } else {
      return path;
    }
  }
};

struct Track {
  std::string title = "";
  std::string album = "";
  std::string artists = "";
  std::string genre = "";
  std::string filename = ""; //unique global track identifier

  int albumTrackNumber = -1;
  int year = -1;
  int duration = -1;

  bool isAssembled;
  Source source;
};

struct Playlist {
  vector<Track> tracks;
  std::string name = "";
  bool isDynamic = false;
  int size() { return distance(tracks.begin(), tracks.end()); }
};
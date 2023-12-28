#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Types{
public:
enum class StorageType{LOCAL,REMOTE,ANY,NONE};
enum class PathType{URL,FILESYSTEMPATH,ANY,NONE};
enum class DataType{DATA,TRACK,PLAYLIST,BLOCKLIST,ALBUM,ARTISTSTRACKS,LOCALDATABASE,ANY,NONE};
enum class Loop{NONE,TRACKONCE,TRACK,PLAYLISTONCE,PLAYLIST};
enum class Event{AUTHENTICATION_TRYED,FILES_UPDATED,SOUNDMAKER_PLAYLIST_SET};
};

class Source{
public:
  string path;
  Types::StorageType storageType;
  Types::PathType pathType;
  Types::DataType dataType;
  Source(string setpath,Types::StorageType setstorageType,Types::PathType setpathType,Types::DataType setdataType);
  Source(string setpath);
  Source();
  string getVlcPath();
};

class Track{
public:
  string title;
  string album;
  string artists;
  string genre;
  string filename;

  int albumTrackNumber;
  int year;
  int duration;

  bool isAssembled;
  Source source;
};

class Playlist{
public:
  vector<Track> tracks;
  string name;
  bool isDynamic;
  void saveLocally();
  void shuffle(int startingOriginalIndex);
};
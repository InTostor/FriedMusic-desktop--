#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Data.hpp"
#include "StandartGlobalUser.hpp"

using namespace std;

class Client : public StandartGlobalCaller {
private:
  bool _authenticated;
  string _username;
  Types::StorageType databaseType;
  cpr::Cookies cookies;

public:
  //   !WARNING! this is extremely unsafe, violates most of the security
  //   policies and maybe geneva convention. Find better way to work with
  //   credentials!
  void authenticate(string username, string password);
  void authenticate();
  string getUsername();
  bool isServerAccessible();
  bool isAuthenticated();
  void downloadDatabase();
  void pullRemote();
  void pushRemote();
  void downloadTrack(vector<string> filenames);
  void downloadTrack(string filename);
  void deleteTrack(string filename);
  Client();
  vector<string> getTracksList(Types::StorageType where);
  vector<string> getPlaylistFiles(Types::StorageType where);
  vector<Source> getPlaylistsSource(Types::StorageType where);
  Source lookupTrack(string filename);
  vector<Source> lookupTrack(vector<string> filenames);
  Track assembleTrack(Track track);
  vector<Track> assembleTracks(vector<Track> tracks);
  Playlist getPlaylistFromSource(Source source, bool assemble = false);
  bool isTrackInPlaylist(Track track, Playlist playlist);
  bool isTrackInPlaylist(Track track, Source source);
  bool isTrackDownloaded(Track track);
  bool isSourceExistsLocally(Source source);
};
#endif
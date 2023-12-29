#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Data.hpp"

using namespace std;


class Client{
private:
bool _authenticated;
string _username;
Types::StorageType databaseType;

public:
void authenticate();
string getUsername();
void registerListener(); // use class listener
bool isServerAccessible();
bool isAuthenticated();
void downloadDatabase();
void pullRemote();
void pushRemote();
void downloadTrack(vector<string> filenames);
void downloadTrack(string filename);
Client();
vector<string> getTracksList(Types::StorageType where);
vector<string> getPlaylistFiles(Types::StorageType where);
vector<Source> getPlaylistsSource(Types::StorageType where);
Source lookupTrack(string filename);
void assembleTrack(Track *track);
void assembleTrack(vector<reference_wrapper<Track>> tracks);

Playlist getPlaylistFromSource(Source source, bool assemble = false);
};

#include <iostream>
#include <string>
#include "../Data.hpp"
#include "../Client.hpp"
#include "../SoundMaker.hpp"

#ifndef ui_HPP_INCLUDED
#define ui_HPP_INCLUDED

using namespace std;

class SoundMaker;
class StandartGlobalUser{
  public:
  SoundMaker *soundmaker;
  Client client;
   void onMediaPlayerMediaChanged(){};
   void onMediaPlayerNothingSpecial(){};
   void onMediaPlayerOpening(){};
   void onMediaPlayerBuffering(){};
   void onMediaPlayerPlaying(){};
   void onMediaPlayerPaused(){};
   void onMediaPlayerStopped(){};
   void onMediaPlayerForward(){};
   void onMediaPlayerBackward(){};
   void onMediaPlayerEndReached(){};
   void onMediaPlayerEncounteredError(){};
   void onMediaPlayerTimeChanged(){};
   void onMediaPlayerPositionChanged(){};
   void onMediaPlayerLengthChanged(){};
   void onMediaPlayerVout(){};
   void onMediaPlayerScrambledChanged(){};
   void onMediaPlayerESAdded(){};
   void onMediaPlayerESDeleted(){};
   void onMediaPlayerESSelected(){};
   void onMediaPlayerCorked(){};
   void onMediaPlayerUncorked(){};
   void onMediaPlayerMuted(){};
   void onMediaPlayerUnmuted(){};
   void onMediaPlayerAudioVolume(){};
   void onMediaPlayerAudioDevice(){};
   void onAuthenticationTryed(){};
   void onFilesUpdated(){};
   void onSoundMakerPlaylistInsert(){};
};

class Icons{
  public:
  static string const PLAY;
  static string const PAUSE;
  static string const PREV;
  static string const NEXT;
  static string const SHUFFLE;
  static string const TOFAVOURITE;
  static string const UNFAVOURITE;
  static string const TOLIST;
  static string const DOWNLOAD;
  static string const DELETE;
  static string const MOREVERT;
  static string const SETTINGS;
};

string const Icons::PLAY = "resource/Octicons-playback-play.svg";
string const Icons::PAUSE = "resource/Octicons-playback-pause.svg";
string const Icons::PREV = "resource/Fast_backward_font_awesome.svg";
string const Icons::NEXT = "resource/Fast_forward_font_awesome.svg";
string const Icons::SHUFFLE = "resource/shuffle.svg";
string const Icons::TOFAVOURITE = "resource/directory_favorites-2.png";
string const Icons::UNFAVOURITE = "resource/directory_favorites-remove-2.png";
string const Icons::TOLIST = "resource/directory_open_file_mydocs-4.png";
string const Icons::DOWNLOAD = "resource/download.svg";
string const Icons::DELETE = "resource/trash-can.svg";
string const Icons::MOREVERT = "resource/more_vert.svg";
string const Icons::SETTINGS = "resource/settings.svg";

#endif
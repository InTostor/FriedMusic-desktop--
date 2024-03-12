#pragma once
#include <QMediaPlayer>
#include <QObject>
#include <QUrl>
#include <iostream>
#include <vector>

#include "Data.hpp"
#include "StandartGlobalUser.hpp"
#include "macro.hpp"

// #include "vlcpp/vlc.hpp"

using namespace std;

class SoundMaker : public StandartGlobalCaller, public QObject {
private:
  bool _shuffled = false;
  Types::Loop _loopMode = Types::Loop::NONE;
  Track currentTrack;
  int _currentTrackIndex = -1;
  Playlist _currentPlaylist;
  Playlist _originalPlaylist;

  // Cuz Qt is bullshit, but better than other
public:
  QMediaPlayer *player;
  void AUTHENTICATION_TRYED();
  void FILES_UPDATED();
  void SOUNDMAKER_PLAYLIST_SET();
  void onMediaPlayerMediaChanged();
  void onMediaPlayerNothingSpecial();
  void onMediaPlayerOpening();
  void onMediaPlayerBuffering();
  void onMediaPlayerPlaying();
  void onMediaPlayerPaused();
  void onMediaPlayerStopped();
  void onMediaPlayerForward();
  void onMediaPlayerBackward();
  void onMediaPlayerEncounteredError();
  void onMediaPlayerTimeChanged();
  void onMediaPlayerPositionChanged();
  void onMediaPlayerLengthChanged();
  void onMediaPlayerVout();
  void onMediaPlayerESAdded();
  void onMediaPlayerESDeleted();
  void onMediaPlayerESSelected();
  void onMediaPlayerCorked();
  void onMediaPlayerUncorked();
  void onMediaPlayerMuted();
  void onMediaPlayerUnmuted();
  void onMediaPlayerAudioVolume();
  void onMediaPlayerAudioDevice();
  void QtStateRedirector();
  void QtMediaRedirector();

  void make();

  void previous();
  void next();

  void setPosition(float pos);
  void setVolume(int vol);
  void play();
  void pause();

  void setTime(float time);
  void setCurrentIndex(int value);
  void setPlaylist(Playlist playlist, int index = 0);
  void setPlaylist(Source playlist);
  void setShuffled(bool value);
  void setUrl(string url);
  void setTrack(Track track);
  void setLoopMode(Types::Loop newLoop);
  int getVolume();
  float getPosition();
  QMediaPlayer::State getState();
  float getTime();
  float getLength();
  Types::Loop getLoopMode();
  Track getTrack();
  bool getIsShuffled();
  bool getIsPlaying();
  Playlist getCurrentPlaylist();
  void onMediaFinished();
};
#pragma once

#include <QMediaPlayer>
#include <QUrl>
#include <iostream>
#include <vector>

#include "Client.hpp"
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
 public slots:
  void AUTHENTICATION_TRYED() {}
  void FILES_UPDATED() {}
  void SOUNDMAKER_PLAYLIST_SET() {}
  void onMediaPlayerMediaChanged() {}
  void onMediaPlayerNothingSpecial() {}
  void onMediaPlayerOpening() {}
  void onMediaPlayerBuffering() {}
  void onMediaPlayerPlaying() {}
  void onMediaPlayerPaused() {}
  void onMediaPlayerStopped() {}
  void onMediaPlayerForward() {}
  void onMediaPlayerBackward() {}
  void onMediaPlayerEncounteredError() {}
  void onMediaPlayerTimeChanged() {}
  void onMediaPlayerPositionChanged() {
    eventProcessor(Types::Event::onMediaPlayerPositionChanged);
  }
  void onMediaPlayerLengthChanged() {}
  void onMediaPlayerVout() {}
  void onMediaPlayerESAdded() {}
  void onMediaPlayerESDeleted() {}
  void onMediaPlayerESSelected() {}
  void onMediaPlayerCorked() {}
  void onMediaPlayerUncorked() {}
  void onMediaPlayerMuted() {}
  void onMediaPlayerUnmuted() {}
  void onMediaPlayerAudioVolume() {}
  void onMediaPlayerAudioDevice() {}
  void QtStateRedirector() {
    switch (player->state()) {
      case QMediaPlayer::StoppedState:
        eventProcessor(Types::Event::onMediaPlayerStopped);
        break;
      case QMediaPlayer::PlayingState:
        eventProcessor(Types::Event::onMediaPlayerPlaying);
        break;
      case QMediaPlayer::PausedState:
        eventProcessor(Types::Event::onMediaPlayerPaused);
        break;
    }
  }
  void QtMediaRedirector() {
    switch (player->mediaStatus()) {
      case QMediaPlayer::UnknownMediaStatus:
        eventProcessor(Types::Event::unknown);
        break;
      case QMediaPlayer::NoMedia:
        eventProcessor(Types::Event::unknown);
        break;
      case QMediaPlayer::LoadingMedia:
        eventProcessor(Types::Event::onMediaPlayerOpening);
        break;
      case QMediaPlayer::LoadedMedia:
        eventProcessor(Types::Event::onMediaPlayerOpened);
        break;
      case QMediaPlayer::StalledMedia:
        eventProcessor(Types::Event::onMediaPlayerCorked);
        break;
      case QMediaPlayer::BufferingMedia:
        eventProcessor(Types::Event::onMediaPlayerBuffering);
        break;
      case QMediaPlayer::BufferedMedia:
        eventProcessor(Types::Event::onMediaPlayerBuffered);
        break;
      case QMediaPlayer::EndOfMedia:
        eventProcessor(Types::Event::onMediaPlayerMediaFinished);
        QtStateRedirector();
        onMediaFinished();
        break;
      case QMediaPlayer::InvalidMedia:
        eventProcessor(Types::Event::unknown);
        break;
      default:
        break;
    }
  }

 public:
  Client client;
  QMediaPlayer *player;
  SoundMaker() {
    player = new QMediaPlayer;
    player->setVolume(0);
    QObject::connect(player, &QMediaPlayer::positionChanged, this,
                     &SoundMaker::onMediaPlayerPositionChanged);
    QObject::connect(player, &QMediaPlayer::stateChanged, this,
                     &SoundMaker::QtStateRedirector);
    QObject::connect(player, &QMediaPlayer::mediaStatusChanged, this,
                     &SoundMaker::QtMediaRedirector);
  }

  void previous() {
    bool shouldPlay = player->state() == QMediaPlayer::PlayingState;
    if (_currentTrackIndex > 0) {
      setCurrentIndex(_currentTrackIndex - 1);
    }
    if (shouldPlay){
      play();
    }
  };
  void next() {
    if (_currentTrackIndex >= _currentPlaylist.size() - 1) {
      setCurrentIndex(0);
    } else {
      setCurrentIndex(_currentTrackIndex + 1);
    }
    play();
  };
  // setters
  void setPosition(float pos) { player->setPosition(pos * player->duration()); }
  void setVolume(int vol) { player->setVolume(vol); }
  void play() { player->play(); }
  void pause() { player->pause(); }

  void setTime(float time) { this->setPosition(player->duration() / time); }
  void setCurrentIndex(int value) {
    _currentTrackIndex = value;
    currentTrack = _currentPlaylist.tracks[value];
    setTrack(currentTrack);
  }
  void setPlaylist(Playlist playlist, int index = 0) {
    _currentPlaylist = playlist;
    _originalPlaylist = playlist;
    if (getIsShuffled()) {
      setShuffled(true);
    }
    setCurrentIndex(index);
    eventProcessor(Types::Event::SOUNDMAKER_PLAYLIST_SET);
  }
  void setPlaylist(Source playlist) {
    Playlist prepared = client.getPlaylistFromSource(playlist);
    setPlaylist(prepared);
  }
  void setShuffled(bool value) { _shuffled = value; }
  void setLoopMode(Types::Loop newLoop) { _loopMode = newLoop; }
  void setUrl(string url) {
    player->setMedia(QUrl(QString::fromStdString(url)));
  }
  void setTrack(Track track) {
    if (track.source.pathType == Types::PathType::URL) {
      player->setMedia(QUrl(QString::fromStdString(track.source.path)));
    } else if (track.source.pathType == Types::PathType::FILESYSTEMPATH) {
      player->setMedia(
          QUrl::fromLocalFile(QString::fromStdString(track.source.path)));
    }
    eventProcessor(Types::Event::onMediaPlayerMediaChanged);
  }
  // getters
  int getVolume() { return player->volume(); }

  float getPosition() {
    int curTime = player->position();
    int maxTime = player->duration();
    if (curTime != 0) {
      float pos = (float)curTime / (float)maxTime;
      return pos;
    } else {
      return 0.0;
    }
  }

  float getTime() { return player->position(); }

  float getLength() { return static_cast<int>(player->duration()); }

  Types::Loop getLoopMode() { return (_loopMode); }
  Track getTrack() { return currentTrack; }

  bool getIsShuffled() { return (_shuffled); }
  bool getIsPlaying() { return player->state() == QMediaPlayer::PlayingState; }
  Playlist getCurrentPlaylist() { return _currentPlaylist; }
  void onMediaFinished() {
    switch (_loopMode) {
      case Types::Loop::NONE:
        next();
        play();
        break;
      case Types::Loop::TRACKONCE:
        setPosition(0);
        play();
        setLoopMode(Types::Loop::NONE);
        break;
      case Types::Loop::TRACK:
        setPosition(0);
        play();
        break;
      case Types::Loop::PLAYLISTONCE:
        next();
        play();
        setLoopMode(Types::Loop::NONE);
        break;
      case Types::Loop::PLAYLIST:
        next();
        play();
        break;
    }
  }
};
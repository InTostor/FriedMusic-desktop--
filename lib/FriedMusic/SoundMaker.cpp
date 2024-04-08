#include "SoundMaker.hpp"
#include "globals.h"
#include <QMediaPlayer>
#include <QObject>
#include <QUrl>
#include <iostream>
#include <vector>

#include "Client.hpp"
#include "Data.hpp"
#include "Library.hpp"
#include "StandartGlobalUser.hpp"
#include "macro.hpp"

using namespace std;

void SoundMaker::AUTHENTICATION_TRYED() {}
void SoundMaker::FILES_UPDATED() {}
void SoundMaker::SOUNDMAKER_PLAYLIST_SET() {}
void SoundMaker::onMediaPlayerMediaChanged() {}
void SoundMaker::onMediaPlayerNothingSpecial() {}
void SoundMaker::onMediaPlayerOpening() {}
void SoundMaker::onMediaPlayerBuffering() {}
void SoundMaker::onMediaPlayerPlaying() {}
void SoundMaker::onMediaPlayerPaused() {}
void SoundMaker::onMediaPlayerStopped() {}
void SoundMaker::onMediaPlayerForward() {}
void SoundMaker::onMediaPlayerBackward() {}
void SoundMaker::onMediaPlayerEncounteredError() {}
void SoundMaker::onMediaPlayerTimeChanged() {}
void SoundMaker::onMediaPlayerPositionChanged() {
  eventHeap.eventProcessor(Types::Event::onMediaPlayerPositionChanged);
  // eventProcessor(Types::Event::onMediaPlayerPositionChanged);
}
void SoundMaker::onMediaPlayerLengthChanged() {}
void SoundMaker::onMediaPlayerVout() {}
void SoundMaker::onMediaPlayerESAdded() {}
void SoundMaker::onMediaPlayerESDeleted() {}
void SoundMaker::onMediaPlayerESSelected() {}
void SoundMaker::onMediaPlayerCorked() {}
void SoundMaker::onMediaPlayerUncorked() {}
void SoundMaker::onMediaPlayerMuted() {}
void SoundMaker::onMediaPlayerUnmuted() {}
void SoundMaker::onMediaPlayerAudioVolume() {}
void SoundMaker::onMediaPlayerAudioDevice() {}
void SoundMaker::QtStateRedirector() {
  switch (player->state()) {
  case QMediaPlayer::StoppedState:
    eventHeap.eventProcessor(Types::Event::onMediaPlayerStopped);
    break;
  case QMediaPlayer::PlayingState:
    eventHeap.eventProcessor(Types::Event::onMediaPlayerPlaying);
    break;
  case QMediaPlayer::PausedState:
    eventHeap.eventProcessor(Types::Event::onMediaPlayerPaused);
    break;
  }
}
void SoundMaker::QtMediaRedirector() {
  switch (player->mediaStatus()) {
  case QMediaPlayer::UnknownMediaStatus:
    eventHeap.eventProcessor(Types::Event::unknown);
    break;
  case QMediaPlayer::NoMedia:
    eventHeap.eventProcessor(Types::Event::unknown);
    break;
  case QMediaPlayer::LoadingMedia:
    eventHeap.eventProcessor(Types::Event::onMediaPlayerOpening);
    break;
  case QMediaPlayer::LoadedMedia:
    eventHeap.eventProcessor(Types::Event::onMediaPlayerOpened);
    break;
  case QMediaPlayer::StalledMedia:
    eventHeap.eventProcessor(Types::Event::onMediaPlayerCorked);
    break;
  case QMediaPlayer::BufferingMedia:
    eventHeap.eventProcessor(Types::Event::onMediaPlayerBuffering);
    break;
  case QMediaPlayer::BufferedMedia:
    eventHeap.eventProcessor(Types::Event::onMediaPlayerBuffered);
    break;
  case QMediaPlayer::EndOfMedia:
    eventHeap.eventProcessor(Types::Event::onMediaPlayerMediaFinished);
    QtStateRedirector();
    onMediaFinished();
    break;
  case QMediaPlayer::InvalidMedia:
    eventHeap.eventProcessor(Types::Event::unknown);
    break;
  default:
    break;
  }
}

// Constructor alternative because of deleted QObject constructor
void SoundMaker::make() {
  player = new QMediaPlayer;
  player->setVolume(0);
  QObject::connect(player, &QMediaPlayer::positionChanged, this,
                   &SoundMaker::onMediaPlayerPositionChanged);
  QObject::connect(player, &QMediaPlayer::stateChanged, this,
                   &SoundMaker::QtStateRedirector);
  QObject::connect(player, &QMediaPlayer::mediaStatusChanged, this,
                   &SoundMaker::QtMediaRedirector);
}
void SoundMaker::previous() {
  if (_currentPlaylist.isDynamic) {
    return;
  }
  bool shouldPlay = player->state() == QMediaPlayer::PlayingState;
  if (_currentTrackIndex > 0) {
    setCurrentIndex(_currentTrackIndex - 1);
  }
  if (shouldPlay) {
    play();
  }
};
void SoundMaker::next() {
  if (_currentPlaylist.isDynamic) {
    Track nextTrack =
        _currentDynamicPlaylist->getNextTrack();
    setTrack(nextTrack);
  } else {
    if (_currentTrackIndex >= _currentPlaylist.size() - 1) {
      setCurrentIndex(0);
    } else {
      setCurrentIndex(_currentTrackIndex + 1);
    }
  }
  play();
};
// setters
void SoundMaker::setPosition(float pos) {
  player->setPosition(pos * player->duration());
}
void SoundMaker::setVolume(int vol) { player->setVolume(vol); }
void SoundMaker::play() {
  player->play();
  eventHeap.eventProcessor(Types::Event::onMediaPlayerPlaying);
}
void SoundMaker::pause() {
  player->pause();
  eventHeap.eventProcessor(Types::Event::onMediaPlayerPaused);
}
void SoundMaker::setTime(float time) {
  this->setPosition(player->duration() / time);
}
void SoundMaker::setCurrentIndex(int value) {
  _currentTrackIndex = value;

  currentTrack = _currentPlaylist.tracks[value];
  setTrack(currentTrack);
}
void SoundMaker::setPlaylist(Playlist playlist, int index) {
  _currentPlaylist = playlist;
  // _originalPlaylist = playlist;
  if (getIsShuffled()) {
    setShuffled(true);
  }
  eventHeap.eventProcessor(Types::Event::SOUNDMAKER_PLAYLIST_SET);
  if (!_currentPlaylist.isDynamic) {
    setCurrentIndex(index);
  } else {
    next();
  }
}
void SoundMaker::setPlaylist(DynamicPlaylistInterface *playlist){
  if (_currentDynamicPlaylist){
    delete _currentDynamicPlaylist;
  }
  _currentDynamicPlaylist = playlist;
  _currentPlaylist = Playlist();
  _currentPlaylist.isDynamic = true;
  next();
}
void SoundMaker::setPlaylist(Source &playlist) {
  Playlist prepared = client.getPlaylistFromSource(playlist);
  setPlaylist(prepared);
}
void SoundMaker::setShuffled(bool value) { _shuffled = value; }
void SoundMaker::setLoopMode(Types::Loop newLoop) {
  _loopMode = newLoop;
  eventHeap.eventProcessor(Types::Event::onMediaPlayerLoopModeChanged);
}
void SoundMaker::setUrl(string url) {
  player->setMedia(QUrl(QString::fromStdString(url)));
}
void SoundMaker::setTrack(Track track) {
  hasSavedToHistory = false;
  if (track.source.pathType == Types::PathType::URL) {
    player->setMedia(QUrl(QString::fromStdString(track.source.path)));
  } else if (track.source.pathType == Types::PathType::FILESYSTEMPATH) {
    player->setMedia(QUrl::fromLocalFile(
        QString::fromStdString(filesystem::absolute(track.source.path))));
  }
  eventHeap.eventProcessor(Types::Event::onMediaPlayerMediaChanged);
}
// getters
int SoundMaker::getVolume() { return player->volume(); }
float SoundMaker::getPosition() {
  int curTime = player->position();
  int maxTime = player->duration();
  if (curTime != 0) {
    float pos = (float)curTime / (float)maxTime;
    return pos;
  } else {
    return 0.0;
  }
}
QMediaPlayer::State SoundMaker::getState() { return player->state(); }
float SoundMaker::getTime() { return player->position(); }
float SoundMaker::getLength() { return static_cast<int>(player->duration()); }
Types::Loop SoundMaker::getLoopMode() { return (_loopMode); }
Track SoundMaker::getTrack() { return currentTrack; }
bool SoundMaker::getIsShuffled() { return (_shuffled); }
bool SoundMaker::getIsPlaying() {
  return player->state() == QMediaPlayer::PlayingState;
}
Playlist SoundMaker::getCurrentPlaylist() { return _currentPlaylist; }
void SoundMaker::onMediaFinished() {
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

void SoundMaker::eventProcessor(const Types::Event &event) {
  if (event == Types::Event::onMediaPlayerPositionChanged) {
    if (!hasSavedToHistory and
        getTime() >= getConfigIntValue("secondsToAddTrackToHistory") * 1000) {
          
      Library::addTrackToFilePlaylist(
          getTrack(), Library::getPlaylistSource("history.fpl"));
      hasSavedToHistory = true;
    }
  }
  // StandartGlobalCaller::eventProcessor(event);
}

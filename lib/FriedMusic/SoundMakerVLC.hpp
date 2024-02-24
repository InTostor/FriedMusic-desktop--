#pragma once

#include <iostream>
#include <vector>

#include "Client.hpp"
#include "Data.hpp"
#include "StandartGlobalUser.hpp"
#include "macro.hpp"
#include "vlcpp/vlc.hpp"

using namespace std;

class SoundMaker : public StandartGlobalCaller {
 private:
  bool _shuffled = false;
  Types::Loop _loopMode = Types::Loop::NONE;
  Track currentTrack;
  int _currentTrackIndex = -1;
  Playlist _currentPlaylist;
  Playlist _originalPlaylist;
  VLC::Instance instance;
  VLC::MediaPlayer player;

 public:
  Client client;
  SoundMaker() {
    instance = VLC::Instance(0, nullptr);
    instance.setUserAgent("Fried Music desktop", "FriedMusic/1.0");
    player = VLC::MediaPlayer(instance);
    VLC::EventManager events = player.eventManager();
    libvlc_event_attach(events, libvlc_MediaPlayerMediaChanged,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerNothingSpecial,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerOpening,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerBuffering,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerPlaying,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerPaused,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerStopped,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerForward,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerBackward,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerEncounteredError,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerTimeChanged,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerPositionChanged,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerLengthChanged,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerVout,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerESAdded,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerESDeleted,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerESSelected,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerCorked,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerUncorked,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerMuted,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerUnmuted,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerAudioVolume,
                        SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerAudioDevice,
                        SoundMaker::vlcEventProcessor, this);
  }

  static void vlcEventProcessor(const struct libvlc_event_t *p_event,
                                void *p_data);

  void previous() {
    if (_currentTrackIndex > 0) {
      setCurrentIndex(_currentTrackIndex - 1);
    }
  };
  void next() {
    if (_currentTrackIndex >= distance(_currentPlaylist.tracks.begin(),
                                       _currentPlaylist.tracks.end()) -
                                  1) {
      setCurrentIndex(0);
    } else {
      setCurrentIndex(_currentTrackIndex + 1);
    }
  };
  void play() { player.play(); };
  void pause() { player.pause(); };
  void stop() { player.stop(); };
  // setters
  void setVolume(int newVolume) {
    player.setVolume(std::clamp(newVolume, 0, 100));
  };
  void setPosition(float newPosition) {
    player.setPosition(std::clamp(newPosition, 0.0f, 1.0f));
  };
  void setTime(float time) { player.setTime(time); }
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
    VLC::Media media(instance, url, VLC::Media::FromType::FromLocation);
    player.setMedia(media);
  }
  void setTrack(Track track) {
    if (track.source.pathType == Types::PathType::URL) {
      VLC::Media media(instance, track.source.getUrlEncodedPath(),
                       VLC::Media::FromType::FromLocation);
      player.setMedia(media);
    } else if (track.source.pathType == Types::PathType::FILESYSTEMPATH) {
      VLC::Media media(instance, track.source.path,
                       VLC::Media::FromType::FromPath);
      player.setMedia(media);
      libvlc_media_release(media);
    }
  }
  // getters
  int getVolume() { return player.volume(); }

  float getPosition() { return player.position(); }

  float getTime() { return player.time(); }

  float getLength() { return player.length(); }

  Types::Loop getLoopMode() { return (_loopMode); }
  Track getTrack() { return currentTrack; }

  bool getIsShuffled() { return (_shuffled); }
  bool getIsPlaying() { return player.isPlaying(); }
  Playlist getCurrentPlaylist() { return _currentPlaylist; }
};

void SoundMaker::vlcEventProcessor(const struct libvlc_event_t *p_event,
                                   void *p_data) {
  switch (p_event->type) {
    case libvlc_MediaPlayerMediaChanged:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerMediaChanged);
      break;
    case libvlc_MediaPlayerNothingSpecial:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerNothingSpecial);
      break;
    case libvlc_MediaPlayerOpening:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerOpening);
      break;
    case libvlc_MediaPlayerBuffering:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerBuffering);
      break;
    case libvlc_MediaPlayerPlaying:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerPlaying);
      break;
    case libvlc_MediaPlayerPaused:
      ((SoundMaker *)p_data)->eventProcessor(Types::Event::onMediaPlayerPaused);
      break;
    case libvlc_MediaPlayerStopped:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerStopped);
      break;
    case libvlc_MediaPlayerForward:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerForward);
      break;
    case libvlc_MediaPlayerBackward:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerBackward);
      break;
    case libvlc_MediaPlayerEncounteredError:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerEncounteredError);
      break;
    case libvlc_MediaPlayerTimeChanged:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerTimeChanged);
      break;
    case libvlc_MediaPlayerPositionChanged:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerPositionChanged);
      break;
    case libvlc_MediaPlayerLengthChanged:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerLengthChanged);
      break;
    case libvlc_MediaPlayerVout:
      ((SoundMaker *)p_data)->eventProcessor(Types::Event::onMediaPlayerVout);
      break;
    case libvlc_MediaPlayerESAdded:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerESAdded);
      break;
    case libvlc_MediaPlayerESDeleted:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerESDeleted);
      break;
    case libvlc_MediaPlayerESSelected:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerESSelected);
      break;
    case libvlc_MediaPlayerCorked:
      ((SoundMaker *)p_data)->eventProcessor(Types::Event::onMediaPlayerCorked);
      break;
    case libvlc_MediaPlayerUncorked:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerUncorked);
      break;
    case libvlc_MediaPlayerMuted:
      ((SoundMaker *)p_data)->eventProcessor(Types::Event::onMediaPlayerMuted);
      break;
    case libvlc_MediaPlayerUnmuted:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerUnmuted);
      break;
    case libvlc_MediaPlayerAudioVolume:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerAudioVolume);
      break;
    case libvlc_MediaPlayerAudioDevice:
      ((SoundMaker *)p_data)
          ->eventProcessor(Types::Event::onMediaPlayerAudioDevice);
      break;
  }
}
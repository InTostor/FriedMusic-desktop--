#pragma once

#include <iostream>
#include <vector>
#include "macro.hpp"
#include "Data.hpp"
#include "ui/ui.hpp"
#include "vlcpp/vlc.hpp"

using namespace std;

class SoundMaker
{
private:
  bool _shuffled = false;
  Types::Loop _loopMode = Types::Loop::NONE;
  Track currentTrack;
  int _currentTrackIndex = -1;
  Playlist _currentPlaylist;
  Playlist _originalPlaylist;
  VLC::Instance instance;
  VLC::MediaPlayer player;

  vector<StandartGlobalUser*> listeners;

public:
  Client client;
  SoundMaker()
  {
    instance = VLC::Instance(0, nullptr);
    instance.setUserAgent("Fried Music desktop", "FriedMusic/1.0");
    player = VLC::MediaPlayer(instance);
    VLC::EventManager events = player.eventManager();
    libvlc_event_attach(events, libvlc_MediaPlayerMediaChanged, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerNothingSpecial, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerOpening, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerBuffering, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerPlaying, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerPaused, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerStopped, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerForward, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerBackward, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerStopping, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerEncounteredError, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerTimeChanged, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerPositionChanged, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerLengthChanged, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerVout, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerESAdded, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerESDeleted, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerESSelected, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerCorked, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerUncorked, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerMuted, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerUnmuted, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerAudioVolume, SoundMaker::vlcEventProcessor, this);
    libvlc_event_attach(events, libvlc_MediaPlayerAudioDevice, SoundMaker::vlcEventProcessor, this);
  }

  static void vlcEventProcessor(const struct libvlc_event_t *p_event, void *p_data);
  void eventProcessor(Types::Event event);
  void registerListeners(StandartGlobalUser* object);
  void registerListeners(vector<StandartGlobalUser*> object);
  void previous();
  void next();
  void play() { player.play(); };
  void pause() { player.pause(); };
  void stop() { player.stopAsync(); };
  // setters
  void setVolume(int newVolume)
  {
    player.setVolume(std::clamp(newVolume, 0, 100));
  };
  void setPosition(float newPosition)
  {
    player.setPosition(std::clamp(newPosition, 0.0f, 1.0f), true);
  };
  void setTime(float time)
  {
    player.setTime(time, true);
  }
  void setCurrentIndex(int value)
  {
    _currentTrackIndex = value;
  }
  void setPlaylist(Playlist &playlist)
  {
    _currentPlaylist = playlist;
    _originalPlaylist = playlist;
    if (getIsShuffled()){
      setShuffled(true);
    }
  }
  void setPlaylist(Source &playlist)
  {
    Playlist prepared = client.getPlaylistFromSource(playlist);
    setPlaylist(prepared);
  }
  void setShuffled(bool value)
  {
    _shuffled = value;
  }
  void setLoopMode(Types::Loop newLoop)
  {
    _loopMode = newLoop;
  }
  void setUrl(const string url)
  {
    VLC::Media media(url,VLC::Media::FromType::FromLocation);
    player.setMedia(media);
  }
  void setTrack(Track track)
  {
  }
  // getters
  int getVolume()
  {
    return player.volume();
  }

  float getPosition()
  {
    return player.position();
  }

  float getTime()
  {
    return player.time();
  }

  float getLength()
  {
    return player.length();
  }

  Types::Loop getLoopMode()
  {
    return (_loopMode);
  }

  bool getIsShuffled()
  {
    return (_shuffled);
  }
};

void SoundMaker::vlcEventProcessor(const struct libvlc_event_t *p_event, void *p_data)
{
  for (StandartGlobalUser *listener : ((SoundMaker *)p_data)->listeners)
  {
    switch (p_event->type)
    {
    case libvlc_MediaPlayerMediaChanged:
      listener->onMediaPlayerMediaChanged();
      break;
    case libvlc_MediaPlayerNothingSpecial:
      listener->onMediaPlayerNothingSpecial();
      break;
    case libvlc_MediaPlayerOpening:
      listener->onMediaPlayerOpening();
      break;
    case libvlc_MediaPlayerBuffering:
      listener->onMediaPlayerBuffering();
      break;
    case libvlc_MediaPlayerPlaying:
      listener->onMediaPlayerPlaying();
      break;
    case libvlc_MediaPlayerPaused:
      listener->onMediaPlayerPaused();
      break;
    case libvlc_MediaPlayerStopped:
      listener->onMediaPlayerStopped();
      break;
    case libvlc_MediaPlayerForward:
      listener->onMediaPlayerForward();
      break;
    case libvlc_MediaPlayerBackward:
      listener->onMediaPlayerBackward();
      break;
    case libvlc_MediaPlayerStopping:
      // test it before use
      listener->onMediaPlayerMediaChanged();
      break;
    case libvlc_MediaPlayerEncounteredError:
      listener->onMediaPlayerEncounteredError();
      break;
    case libvlc_MediaPlayerTimeChanged:
      listener->onMediaPlayerTimeChanged();
      break;
    case libvlc_MediaPlayerPositionChanged:
      listener->onMediaPlayerPositionChanged();
      break;
    case libvlc_MediaPlayerLengthChanged:
      listener->onMediaPlayerLengthChanged();
      break;
    case libvlc_MediaPlayerVout:
      listener->onMediaPlayerVout();
      break;
    case libvlc_MediaPlayerESAdded:
      listener->onMediaPlayerESAdded();
      break;
    case libvlc_MediaPlayerESDeleted:
      listener->onMediaPlayerESDeleted();
      break;
    case libvlc_MediaPlayerESSelected:
      listener->onMediaPlayerESSelected();
      break;
    case libvlc_MediaPlayerCorked:
      listener->onMediaPlayerCorked();
      break;
    case libvlc_MediaPlayerUncorked:
      listener->onMediaPlayerUncorked();
      break;
    case libvlc_MediaPlayerMuted:
      listener->onMediaPlayerMuted();
      break;
    case libvlc_MediaPlayerUnmuted:
      listener->onMediaPlayerUnmuted();
      break;
    case libvlc_MediaPlayerAudioVolume:
      listener->onMediaPlayerAudioVolume();
      break;
    case libvlc_MediaPlayerAudioDevice:
      listener->onMediaPlayerAudioDevice();
      break;
    }
  }
}
void SoundMaker::eventProcessor(Types::Event event)
{
  for (StandartGlobalUser *listener : listeners)
  {
    switch (event)
    {
    case Types::Event::AUTHENTICATION_TRYED:
      listener->onAuthenticationTryed();
      break;
    case Types::Event::FILES_UPDATED:
      listener->onFilesUpdated();
      break;
    case Types::Event::SOUNDMAKER_PLAYLIST_SET:
      listener->onSoundMakerPlaylistInsert();
      break;
    }
  }
}

void SoundMaker::registerListeners(StandartGlobalUser* object){
  listeners.push_back(object);
}

void SoundMaker::registerListeners(vector<StandartGlobalUser*> objects){
  listeners.insert(std::end(listeners),std::begin(objects),std::end(objects));
}

#ifndef SoundMaker_HPP_INCLUDED
#define SoundMaker_HPP_INCLUDED

#include <iostream>
#include <vector>
#include "macro.hpp"
#include "Data.hpp"
#include "ui/ui.hpp"
#include "vlcpp/vlc.hpp"

using namespace std;

class SoundMaker{
  private:
  bool isShuffled = false;
  Types::Loop loopMode = Types::Loop::NONE;
  Track currentTrack;
  int currentTrackIndex = -1;
  Playlist currentPlaylist;
  VLC::Instance instance;
  VLC::MediaPlayer player;

  vector<StandartGlobalUser> listeners;

  public:

  SoundMaker(){
    instance = VLC::Instance(0,nullptr);
    instance.setUserAgent("Fried Music desktop","FriedMusic/1.0");
    player = VLC::MediaPlayer(instance);
    VLC::EventManager events = player.eventManager();
    libvlc_event_attach(events,libvlc_MediaPlayerMediaChanged,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerNothingSpecial,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerOpening,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerBuffering,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerPlaying,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerPaused,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerStopped,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerForward,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerBackward,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerStopping,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerEncounteredError,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerTimeChanged,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerPositionChanged,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerLengthChanged,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerVout,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerESAdded,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerESDeleted,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerESSelected,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerCorked,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerUncorked,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerMuted,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerUnmuted,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerAudioVolume,SoundMaker::vlcEventProcessor,this);
    libvlc_event_attach(events,libvlc_MediaPlayerAudioDevice,SoundMaker::vlcEventProcessor,this);
  }
  
  static void vlcEventProcessor(const struct libvlc_event_t *p_event, void *p_data);
  void eventProcessor(Types::Event event){};
  void registerListeners(StandartGlobalUser object){}
  void previous(){}
  void next(){}
  void play(){}
  void pause(){}
  void stop(){}
  // setters
  void setVolume(int newVolume){}
  void setPosition(float newPosition){}
  void setTime(float time){}
  void setCurrentIndex(int value){}
  void setPlaylist(Playlist playlist){}
  void setShuffled(bool value){}
  void setLoopMode(Types::Loop newLoop){}
  void setUrl(string url){}
  void setTrack(Track track){}
  // getters
  int getVolume(){}
  float getPosition(){}
  float getTime(){}
  float getLength(){}
  Types::Loop getLoopMode(){}
  bool getIsShuffled(){}

};






#endif
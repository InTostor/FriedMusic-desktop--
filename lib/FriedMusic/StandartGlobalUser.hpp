#pragma once
#include <QObject>
#include <QWidget>
#include <iostream>
#include <vector>

#include "Data.hpp"

using namespace std;

class SoundMaker;
class Client;
class MainWindow;
class StandartGlobalCaller;
class StandartGlobalUser {
 public:
  Client *client;
  SoundMaker *soundmaker;
  StandartGlobalCaller *mainWindow;

  virtual void eventProcessor(const Types::Event &event) {}

  void setGlobals(SoundMaker *sm, Client *cl) {
    soundmaker = sm;
    client = cl;
  }
  virtual ~StandartGlobalUser() = default;
};

/// @brief Calls methods on stored listeners. Callbacks
class StandartGlobalCaller {
 protected:
  vector<StandartGlobalUser *> listeners;
  vector<StandartGlobalCaller *> callerListeners;

 public:
  void registerListeners(StandartGlobalUser *object) {
    listeners.push_back(object);
  };
  void registerListeners(vector<StandartGlobalUser *> objects) {
    listeners.insert(std::end(listeners), std::begin(objects),
                     std::end(objects));
  };
  void unregisterListener(StandartGlobalUser *object) {
    vector<StandartGlobalUser *>::iterator toErase;
    toErase = find(listeners.begin(), listeners.end(), object);
    listeners.erase(toErase);
  }

  void registerCallerListeners(StandartGlobalCaller *object) {
    callerListeners.push_back(object);
  };
  void registerCallerListeners(vector<StandartGlobalCaller *> objects) {
    callerListeners.insert(std::end(callerListeners), std::begin(objects),
                           std::end(objects));
  };
  void unregisterCallerListener(StandartGlobalCaller *object) {
    vector<StandartGlobalCaller *>::iterator toErase;
    toErase = find(callerListeners.begin(), callerListeners.end(), object);
    callerListeners.erase(toErase);
  }
  virtual void eventProcessor(const Types::Event &event){
    for (StandartGlobalUser *listener : listeners) {
      listener->eventProcessor(event);
    }
    for (StandartGlobalCaller *listener : callerListeners) {
      listener->eventProcessor(event);
    }
  }

  // virtual void eventProcessor(const Types::Event &event) {
  //   for (StandartGlobalUser *listener : listeners) {
  //     switch (event) {
  //       case Types::Event::AUTHENTICATION_TRYED:
  //         listener->onAuthenticationTryed();
  //         break;
  //       case Types::Event::FILES_UPDATED:
  //         listener->onFilesUpdated();
  //         break;
  //       case Types::Event::SOUNDMAKER_PLAYLIST_SET:
  //         listener->onSoundMakerPlaylistInsert();
  //         break;
  //       case Types::Event::onMediaPlayerMediaChanged:
  //         listener->onMediaPlayerMediaChanged();
  //         break;
  //       case Types::Event::onMediaPlayerNothingSpecial:
  //         listener->onMediaPlayerNothingSpecial();
  //         break;
  //       case Types::Event::onMediaPlayerOpening:
  //         listener->onMediaPlayerOpening();
  //         break;
  //       case Types::Event::onMediaPlayerBuffering:
  //         listener->onMediaPlayerBuffering();
  //         break;
  //       case Types::Event::onMediaPlayerPlaying:
  //         listener->onMediaPlayerPlaying();
  //         break;
  //       case Types::Event::onMediaPlayerPaused:
  //         listener->onMediaPlayerPaused();
  //         break;
  //       case Types::Event::onMediaPlayerStopped:
  //         listener->onMediaPlayerStopped();
  //         break;
  //       case Types::Event::onMediaPlayerForward:
  //         listener->onMediaPlayerForward();
  //         break;
  //       case Types::Event::onMediaPlayerBackward:
  //         listener->onMediaPlayerBackward();
  //         break;
  //       case Types::Event::onMediaPlayerEncounteredError:
  //         listener->onMediaPlayerEncounteredError();
  //         break;
  //       case Types::Event::onMediaPlayerTimeChanged:
  //         listener->onMediaPlayerTimeChanged();
  //         break;
  //       case Types::Event::onMediaPlayerPositionChanged:
  //         listener->onMediaPlayerPositionChanged();
  //         break;
  //       case Types::Event::onMediaPlayerLengthChanged:
  //         listener->onMediaPlayerLengthChanged();
  //         break;
  //       case Types::Event::onMediaPlayerVout:
  //         listener->onMediaPlayerVout();
  //         break;
  //       case Types::Event::onMediaPlayerESAdded:
  //         listener->onMediaPlayerESAdded();
  //         break;
  //       case Types::Event::onMediaPlayerESDeleted:
  //         listener->onMediaPlayerESDeleted();
  //         break;
  //       case Types::Event::onMediaPlayerESSelected:
  //         listener->onMediaPlayerESSelected();
  //         break;
  //       case Types::Event::onMediaPlayerCorked:
  //         listener->onMediaPlayerCorked();
  //         break;
  //       case Types::Event::onMediaPlayerUncorked:
  //         listener->onMediaPlayerUncorked();
  //         break;
  //       case Types::Event::onMediaPlayerMuted:
  //         listener->onMediaPlayerMuted();
  //         break;
  //       case Types::Event::onMediaPlayerUnmuted:
  //         listener->onMediaPlayerUnmuted();
  //         break;
  //       case Types::Event::onMediaPlayerAudioVolume:
  //         listener->onMediaPlayerAudioVolume();
  //         break;
  //       case Types::Event::onMediaPlayerAudioDevice:
  //         listener->onMediaPlayerAudioDevice();
  //         break;
  //     }
  //   }
  //   for (StandartGlobalCaller *callerListener : callerListeners) {
  //     callerListener->eventProcessor(event);
  //   }
  // }
};
#pragma once
// #include <QObject>
#include <QWidget>
#include <QtConcurrent>
#include <iostream>
#include <qobject.h>
#include <vector>

#include "Data.hpp"
// #include "globals.h"

using namespace std;

class SoundMaker;
class Client;
class MainWindow;
class StandartGlobalCaller;
class StandartGlobalUser {
public:
  StandartGlobalCaller *mainWindow;
  virtual void eventProcessor(const Types::Event &event) {}

  virtual ~StandartGlobalUser() = default;
};

/// @brief Calls methods on stored listeners. Callbacks
class StandartGlobalCaller {
protected:
  vector<StandartGlobalUser *> listeners;
  vector<StandartGlobalCaller *> callerListeners;

public:
  void registerListeners(StandartGlobalUser *object) {
    // cout << "register: " << object << endl;
    if (std::find(listeners.begin(), listeners.end(), object) ==
        listeners.end()) {
      listeners.push_back(object);
    }
  };
  void registerListeners(vector<StandartGlobalUser *> objects) {
    listeners.insert(end(listeners), begin(objects), end(objects));
  };
  void unregisterListener(StandartGlobalUser *object) {
    // cout << "unregister: " << object << endl;
    vector<StandartGlobalUser *>::iterator toErase;
    toErase = find(listeners.begin(), listeners.end(), object);
    listeners.erase(toErase);
  }

  void registerCallerListeners(StandartGlobalCaller *object) {
    callerListeners.push_back(object);
  };
  void registerCallerListeners(vector<StandartGlobalCaller *> objects) {
    callerListeners.insert(end(callerListeners), begin(objects), end(objects));
  };
  void unregisterCallerListener(StandartGlobalCaller *object) {
    vector<StandartGlobalCaller *>::iterator toErase;
    toErase = find(callerListeners.begin(), callerListeners.end(), object);
    callerListeners.erase(toErase);
  }
  void eventProcessor(const Types::Event &event, bool async = false) {

    for (StandartGlobalUser *listener : listeners) {
      // !HEISENBUG! sometimes there is a phantom address, which is not in the
      // !listeners array. This will cause SIGSEGV
      if (listener and std::find(listeners.begin(), listeners.end(),
                                 listener) != listeners.end()) {
        // cout << "event: " << listener << endl;
        if (async) {
          QtConcurrent::run(listener, &StandartGlobalUser::eventProcessor,
                            event);

        } else {
          listener->eventProcessor(event);
        }
      }
    }
    for (StandartGlobalCaller *listener : callerListeners) {
      if (listener and std::find(callerListeners.begin(), callerListeners.end(),
                                 listener) != callerListeners.end()) {
        listener->eventProcessor(event);
      }
    }
  }
};

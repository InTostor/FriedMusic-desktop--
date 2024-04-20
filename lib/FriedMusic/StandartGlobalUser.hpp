#pragma once
// #include <QObject>
#include <QWidget>
#include <QtConcurrent>
#include <iostream>
#include <qobject.h>
#include <vector>

#include "Data.hpp"
#include "globals.h"

using namespace std;

struct GlobalListenerSubscription{
  
};

class StandartGlobalUser {
public:
// automatic (un)subscription to events
  StandartGlobalUser(void);
  virtual void eventProcessor(const Types::Event &event);
  virtual ~StandartGlobalUser();
};

/// @brief Calls methods on stored listeners. Callbacks
class StandartGlobalCaller {
protected:
  vector<StandartGlobalUser *> listeners = {};

public:
  void registerListeners(StandartGlobalUser *object);
  void registerListeners(vector<StandartGlobalUser *> objects);

  void unregisterListener(StandartGlobalUser *object);

  void eventProcessor(const Types::Event &event, bool async = false);
};

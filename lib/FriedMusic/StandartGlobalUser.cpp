#include <QtConcurrent>
#include <iostream>
#include <vector>

#include "Data.hpp"
#include "StandartGlobalUser.hpp"
#include "globals.h"
#include <future>

using namespace std;

StandartGlobalUser::StandartGlobalUser(void) {
  eventHeap.registerListeners(this);
}
void StandartGlobalUser::eventProcessor(const Types::Event &event) {}
StandartGlobalUser::~StandartGlobalUser() {
  eventHeap.unregisterListener(this);
};

/// @brief Calls methods on stored listeners. Callbacks

void StandartGlobalCaller::registerListeners(StandartGlobalUser *object) {

  if (find(listeners.begin(), listeners.end(), object) == listeners.end()) {
    listeners.push_back(object);
    cout << "registered listener: " << object  << endl;
  } else {
    cout << "Cannot register listener: " << object << endl;
  }
};

void StandartGlobalCaller::registerListeners(
    vector<StandartGlobalUser *> objects) {
  listeners.insert(end(listeners), begin(objects), end(objects));
};

void StandartGlobalCaller::unregisterListener(StandartGlobalUser *object) {
  vector<StandartGlobalUser *>::iterator toErase;
  toErase = find(listeners.begin(), listeners.end(), object);
  listeners.erase(toErase);
}

void StandartGlobalCaller::eventProcessor(const Types::Event &event,
                                          bool async) {
  for (StandartGlobalUser *listener : listeners) {
    // !HEISENBUG! sometimes there is a phantom address, which is not in the
    // !listeners array. This will cause SIGSEGV
    if (listener and
        find(listeners.begin(), listeners.end(), listener) != listeners.end()) {
      cout << "Calling event " << event << " on the: " << listener << endl;
      if (async) {
        std::async(std::launch::async, &StandartGlobalUser::eventProcessor,
                   listener, event);
        // QtConcurrent::run(listener, &StandartGlobalUser::eventProcessor,
        // event);

      } else {
        listener->eventProcessor(event);
      }
    }else{
      cout << "Tryed to call event " << event << " on not bad listener: " << listener<<endl;
    }
  }
}

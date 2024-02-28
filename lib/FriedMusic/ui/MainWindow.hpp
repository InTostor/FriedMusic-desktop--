#pragma once
#include <QMetaObject>
#include <QSplitter>
#include <QVBoxLayout>
#include <QWidget>
#include <Qt>

#include "lib/FriedMusic/StandartGlobalUser.hpp"
#include "lib/FriedMusic/ui/ui.hpp"
#include "lib/FriedMusic/ui/widgets/Finder.h"
#include "lib/FriedMusic/ui/widgets/Player.h"
#include "lib/FriedMusic/ui/widgets/StatusBar.h"
#include "lib/FriedMusic/ui/widgets/TrackList.h"

class MainWindow : public virtual StandartGlobalUser,
                   public QWidget,
                   public StandartGlobalCaller {
 public:
  Player *playerWidget;
  Finder *finderWidget;
  StatusBar *statusBarWidget;
  QSplitter *horizontalSplitter;
  QSplitter *playerSplitter;
  TrackList *currentTrackListWidget;
  // finder, status bar, other
  void setupUi() {
    playerWidget = new Player();
    playerWidget->setGlobals(this->soundmaker, this->client);
    finderWidget = new Finder();
    finderWidget->setGlobals(this->soundmaker, this->client);
    statusBarWidget = new StatusBar();
    statusBarWidget->setGlobals(this->soundmaker, this->client);
    currentTrackListWidget = new TrackList();
    currentTrackListWidget->setGlobals(this->soundmaker, this->client);

    registerListeners(playerWidget);
    registerListeners(finderWidget);
    registerListeners(statusBarWidget);
    registerListeners(currentTrackListWidget);

    playerWidget->mainWindow = this;
    finderWidget->mainWindow = this;
    statusBarWidget->mainWindow = this;
    currentTrackListWidget->mainWindow = this;

    soundmaker->registerCallerListeners(this);
    client->registerCallerListeners(this);

    playerWidget->setupUi();
    finderWidget->setupUi();
    statusBarWidget->setupUi();
    currentTrackListWidget->setupUi();

    playerSplitter = new QSplitter(Qt::Vertical, nullptr);
    playerSplitter->setHandleWidth(5);
    playerSplitter->addWidget(playerWidget);
    playerSplitter->addWidget(currentTrackListWidget);

    horizontalSplitter = new QSplitter(Qt::Horizontal, nullptr);
    horizontalSplitter->setHandleWidth(5);
    horizontalSplitter->setMaximumSize(9999, 9999);
    horizontalSplitter->addWidget(playerSplitter);
    horizontalSplitter->addWidget(finderWidget);
    horizontalSplitter->setStretchFactor(1, 1);

    this->setWindowTitle("Fried Music");
    this->setWindowIcon(QIcon("resource/logo.ico"));
    
    QVBoxLayout *layout;
    layout = new QVBoxLayout(this);

    layout->addWidget(statusBarWidget);
    layout->addWidget(horizontalSplitter);
  }
  MainWindow() { soundmaker = new SoundMaker(); }
  void eventProcessor(const Types::Event &event) override {
    for (StandartGlobalUser *listener : listeners) {
      listener->eventProcessor(event);
    }
    for (StandartGlobalCaller *callerListener : callerListeners) {
      callerListener->eventProcessor(event);
    }
  }
};

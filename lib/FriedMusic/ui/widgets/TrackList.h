/********************************************************************************
** Form generated from reading UI file 'TrackLineYosydD.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TRACKLIST_H
#define TRACKLIST_H

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>

#include "../../StandartGlobalUser.hpp"
#include "../../SoundMaker.hpp"
#include "../../macro.hpp"
#include "../ui.hpp"
#include "TrackLine.h"
#include "../../Data.hpp"
#include "../MainWindow.hpp"


class TrackList : public virtual StandartGlobalUser, public QWidget {
 public:
  QVBoxLayout *verticalLayout;
  QListWidget *listWidget;

  void setupUi() {
    if (this->QWidget::objectName().isEmpty())
      this->QWidget::setObjectName(QString::fromUtf8("form"));
    this->resize(400, 300);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    listWidget = new QListWidget(this);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));

    verticalLayout->addWidget(listWidget);
    onSoundMakerPlaylistInsert();
  };
  void setPlaylist(Playlist playlist) {
    qDeleteAll(listWidget->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
    int index = 0;
    for (Track track : playlist.tracks) {
      TrackLine *trackLine = new TrackLine();
      trackLine->setGlobals(soundmaker,client);
      trackLine->mainWindow = mainWindow;
      trackLine->setupUi();
      trackLine->setTrack(track,index);
      mainWindow->registerListeners(trackLine);      
      
      QListWidgetItem *widgetItem = new QListWidgetItem();
      
      listWidget->addItem(widgetItem);      
      listWidget->setItemWidget(widgetItem,trackLine);
      widgetItem->setSizeHint(trackLine->sizeHint());
      index++;
    }
  };
  void onSoundMakerPlaylistInsert(){
    Playlist currentPlaylist = soundmaker->getCurrentPlaylist();
    if (&currentPlaylist){
      setPlaylist(currentPlaylist);
    }
  }
  void onMediaPlayerPlaying(){
    onSoundMakerPlaylistInsert();
  }
  void eventProcessor(const Types::Event &event) {
    switch (event)
    {
    case Types::Event::SOUNDMAKER_PLAYLIST_SET:
      onSoundMakerPlaylistInsert();
      break;
    
    default:
      break;
    }
  }
};
#endif

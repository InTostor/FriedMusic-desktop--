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

#include "../../Data.hpp"
#include "../../SoundMaker.hpp"
#include "../../StandartGlobalUser.hpp"
#include "../../macro.hpp"
#include "../MainWindow.hpp"
#include "../ui.hpp"
#include "TrackLine.h"
#include "globals.h"


// Currently this class is only for track list under the player widget
class TrackList : public virtual StandartGlobalUser, public QWidget, public virtual PlaylistHolder {
public:
  QVBoxLayout *verticalLayout;
  QListWidget *listWidget;
  vector<TrackLine *> lines;

  void setupUi() {
    if (this->QWidget::objectName().isEmpty())
      this->QWidget::setObjectName(QString::fromUtf8("form"));
    this->resize(500, 300);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    listWidget = new QListWidget(this);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setBatchSize(20);
    listWidget->setLayoutMode(QListView::Batched);
    listWidget->setViewMode(QListView::ListMode);
    listWidget->setFlow(QListView::TopToBottom);
    listWidget->setResizeMode(QListView::Adjust);

    verticalLayout->addWidget(listWidget);
    onSoundMakerPlaylistInsert();
  };
  void setPlaylist(Playlist &playlist, bool autoAssemble = true) {
    listWidget->clear();
    lines.clear();
    bool isPlaylistValid = (playlist.size()>0);
    if (!isPlaylistValid){
      return;
    }
    if (autoAssemble and !playlist.tracks[0].isAssembled){
      playlist.tracks = client.assembleTracks(playlist.tracks);
    }
    
    
    int index = 0;
    for (Track track : playlist.tracks) {
      TrackLine *trackLine = new TrackLine();
      trackLine->setPlaylistHolder(this);

      trackLine->setupUi();
      trackLine->setTrack(track, playlist, index);
      


      lines.push_back(trackLine);
      QListWidgetItem *widgetItem = new QListWidgetItem();

      listWidget->addItem(widgetItem);
      listWidget->setItemWidget(widgetItem, trackLine);
      widgetItem->setSizeHint(trackLine->sizeHint());
      index++;
    }
    // listWidget->setMinimumWidth(listWidget->sizeHintForColumn(0));
    // this->setMinimumWidth(listWidget->sizeHintForColumn(0));
  };
  void onSoundMakerPlaylistInsert() {
    Playlist currentPlaylist = soundmaker->getCurrentPlaylist();
    setPlaylist(currentPlaylist);
  }
  void onFilesUpdated() {
    Source favSource("./userdata/favourite.fpl", Types::StorageType::LOCAL,
                     Types::PathType::FILESYSTEMPATH,
                     Types::DataType::PLAYLIST);
    Playlist currentPlaylist = soundmaker->getCurrentPlaylist();
    for (int i = 0; i < lines.size(); i++) {
      // update each
      bool isInFavourite =
          client.isTrackInPlaylist(currentPlaylist.tracks[i], favSource);
      bool isDownloaded = client.isTrackDownloaded(currentPlaylist.tracks[i]);
      lines[i]->updateRelation(isInFavourite, isDownloaded);
    }
  }
  void onMediaPlayerPlaying() { onSoundMakerPlaylistInsert(); }
  void eventProcessor(const Types::Event &event) {
    switch (event) {
    case Types::Event::SOUNDMAKER_PLAYLIST_SET:
      onSoundMakerPlaylistInsert();
      break;
    case Types::Event::FILES_UPDATED:
      onFilesUpdated();
      break;
    default:
      break;
    }
  }
  Playlist getHoldedPlaylist(){
    return soundmaker->getCurrentPlaylist();
  }
};
#endif

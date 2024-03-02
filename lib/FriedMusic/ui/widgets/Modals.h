#pragma once

#include "Data.hpp"
#include "StandartGlobalUser.hpp"
#include "macro.hpp"
#include "ui/ui.hpp"
#include <QApplication>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#include "Library.hpp"

class TrackActionsModal : public virtual StandartGlobalUser, public QWidget {

public:
  QVBoxLayout *mainLayout;
  QCheckBox *downloadCheckbox;
  QCheckBox *favouriteCheckbox;
  Track _track;

  void setup(Track track) {
    _track = track;
    if (this->objectName().isEmpty())
      this->setObjectName(QString::fromUtf8("this"));
    this->resize(400, 300);
    this->setWindowFlag(Qt::Popup);
    mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    downloadCheckbox = new QCheckBox(this);
    downloadCheckbox->setObjectName(QString::fromUtf8("downloadCheckbox"));

    mainLayout->addWidget(downloadCheckbox);

    favouriteCheckbox = new QCheckBox(this);
    favouriteCheckbox->setObjectName(QString::fromUtf8("favouriteCheckbox"));

    mainLayout->addWidget(favouriteCheckbox);

    downloadCheckbox->setText("Download");
    favouriteCheckbox->setText("Favourite");

    if (client->isTrackDownloaded(track)) {
      downloadCheckbox->setCheckState(Qt::Checked);
    } else {
      downloadCheckbox->setCheckState(Qt::Unchecked);
    }
    Source favourite = Library::getPlaylistSource("favourite.fpl");
    Playlist favouritePlaylist = client->getPlaylistFromSource(favourite);
    if (client->isTrackInPlaylist(_track, favourite)) {
      favouriteCheckbox->setCheckState(Qt::Checked);
    } else {
      favouriteCheckbox->setCheckState(Qt::Unchecked);
    }
    connect(downloadCheckbox, &QCheckBox::pressed, this,
            &TrackActionsModal::onDownloadPressed);
    connect(favouriteCheckbox, &QCheckBox::pressed, this,
            &TrackActionsModal::onFavouritePressed);

    QMetaObject::connectSlotsByName(this);
  } // setupUi
  void onDownloadPressed() {
    Types::StorageType existence = Library::isSourceExists(_track.source);
    if (existence == Types::StorageType::LOCAL ||
        existence == Types::StorageType::ANY) {
      Library::deleteTrack(_track);
    } else {
      client->downloadTrack(_track.filename);
    }
    close();
  }
  void onFavouritePressed() {
    Source favourite = Library::getPlaylistSource("favourite.fpl");
    Playlist favouritePlaylist = client->getPlaylistFromSource(favourite);
    if (client->isTrackInPlaylist(_track, favourite)) {
      vector<Track>::iterator it = std::find_if(
          favouritePlaylist.tracks.begin(), favouritePlaylist.tracks.end(),
          [&](Track const &t) { return t.filename == _track.filename; });
      favouritePlaylist.tracks.erase(it);
    } else {
      favouritePlaylist.tracks.push_back(_track);
    }
    Library::savePlaylistLocally(favouritePlaylist,client);
    close();
  }
};

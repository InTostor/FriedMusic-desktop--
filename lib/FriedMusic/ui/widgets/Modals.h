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
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qwidget.h>

#include "Library.hpp"


class AddTrackToPlaylistWindow : public virtual StandartGlobalUser, public QWidget {

public:
  QVBoxLayout *mainLayout;
  Source _trackSource;
  QComboBox *playlistSelector;
  QPushButton *confirmButton;

  void setup(Source trackSource) {
    _trackSource = trackSource;
    if (this->objectName().isEmpty())
      this->setObjectName(QString::fromUtf8("this"));
    this->setWindowTitle("add track to playlist");
    this->resize(500, 300);
    mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));

    playlistSelector = new QComboBox;
    vector<Source> playlistSources = Library::getLocalPlaylistSources();
    for (Source plSource : playlistSources){
      string playlistName = filesystem::path(plSource.path).filename();
      playlistSelector->addItem(QString::fromStdString(playlistName));
    }
    confirmButton = new QPushButton(this);
    confirmButton->setText("Add");
    mainLayout->addWidget(playlistSelector);
    mainLayout->addWidget(confirmButton);

    connect(confirmButton,&QPushButton::pressed,this,&AddTrackToPlaylistWindow::onConfirm);
    QMetaObject::connectSlotsByName(this);
  } // setupUi
  void onConfirm(){
    Playlist targetPlaylist = client.getPlaylistFromSource(
      Library::getPlaylistSource(playlistSelector->currentText().toStdString()),
      false
      );
    Track madeTrack;
    madeTrack.source = _trackSource;
    madeTrack.filename = filesystem::path(_trackSource.path).filename();
    cout << madeTrack.filename << endl;
    targetPlaylist.tracks.push_back(madeTrack);
    Library::savePlaylistLocally(targetPlaylist);
    close();
  }
};

class TrackActionsModal : public virtual StandartGlobalUser, public QWidget {

public:
  QVBoxLayout *mainLayout;
  QCheckBox *downloadCheckbox;
  QCheckBox *favouriteCheckbox;
  QPushButton *addToPlaylistButton;
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

    addToPlaylistButton = new QPushButton(this);
    mainLayout->addWidget(addToPlaylistButton);

    downloadCheckbox->setText("Download");
    favouriteCheckbox->setText("Favourite");
    addToPlaylistButton->setText("add to");

    if (client.isTrackDownloaded(track)) {
      downloadCheckbox->setCheckState(Qt::Checked);
    } else {
      downloadCheckbox->setCheckState(Qt::Unchecked);
    }
    Source favourite = Library::getPlaylistSource("favourite.fpl");
    Playlist favouritePlaylist = client.getPlaylistFromSource(favourite);
    if (client.isTrackInPlaylist(_track, favourite)) {
      favouriteCheckbox->setCheckState(Qt::Checked);
    } else {
      favouriteCheckbox->setCheckState(Qt::Unchecked);
    }
    connect(downloadCheckbox, &QCheckBox::pressed, this,
            &TrackActionsModal::onDownloadPressed);
    connect(favouriteCheckbox, &QCheckBox::pressed, this,
            &TrackActionsModal::onFavouritePressed);
    connect(addToPlaylistButton, &QPushButton::pressed, this,
            &TrackActionsModal::onAddToPressed);

    QMetaObject::connectSlotsByName(this);
  } // setupUi
  void onDownloadPressed() {
    Types::StorageType existence = Library::isSourceExists(_track.source);
    if (existence == Types::StorageType::LOCAL ||
        existence == Types::StorageType::ANY) {
      Library::deleteTrack(_track);
    } else {
      client.downloadTrack(_track.filename);
    }
    close();
  }
  void onFavouritePressed() {
    Source favourite = Library::getPlaylistSource("favourite.fpl");
    Playlist favouritePlaylist = client.getPlaylistFromSource(favourite,false);
    if (client.isTrackInPlaylist(_track, favourite)) {
      vector<Track>::iterator it = std::find_if(
          favouritePlaylist.tracks.begin(), favouritePlaylist.tracks.end(),
          [&](Track const &t) { return t.filename == _track.filename; });
      favouritePlaylist.tracks.erase(it);
    } else {
      favouritePlaylist.tracks.push_back(_track);
    }
    Library::savePlaylistLocally(favouritePlaylist);
    close();
  }
  void onAddToPressed() {
    AddTrackToPlaylistWindow *addWindow = new AddTrackToPlaylistWindow();
    addWindow->setup(_track.source);
    QPoint globalCursorPos = QCursor::pos();
    addWindow->setGeometry(globalCursorPos.x(), globalCursorPos.y(),
                       addWindow->geometry().x(), addWindow->geometry().y());
    addWindow->show();
    close();
  }
};

class PlaylistActionsModal : public virtual StandartGlobalUser, public QWidget {

public:
  QVBoxLayout *mainLayout;
  Source _playlistSource;
  QPushButton *editButton;

  void setup(Source playlistSource) {
    _playlistSource = playlistSource;
    if (this->objectName().isEmpty())
      this->setObjectName(QString::fromUtf8("this"));
    this->resize(400, 300);
    this->setWindowFlag(Qt::Popup);
    mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));

    editButton = new QPushButton(this);
    editButton->setText("Edit");
    mainLayout->addWidget(editButton);

    QMetaObject::connectSlotsByName(this);
  } // setupUi
};


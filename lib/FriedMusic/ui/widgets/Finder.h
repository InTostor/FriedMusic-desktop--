/********************************************************************************
** Form generated from reading UI file 'Finder.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FINDER_H
#define FINDER_H

#include <QApplication>
#include <QCompleter>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QScrollArea>
#include <QStandardItemModel>
#include <QTabWidget>
#include <QToolBox>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>
#include <qtoolbox.h>

#include "Library.hpp"

#include "../../StandartGlobalUser.hpp"
#include "../ui.hpp"
#include "TrackLine.h"
#include "PlaylistLine.h"
#include "TrackList.h"
#include "globals.h"


class Finder : public virtual StandartGlobalUser, public QWidget, public PlaylistHolder {
public:
  QGridLayout *gridLayout;
  QTabWidget *tab;
  QWidget *searchTab;
  QVBoxLayout *verticalLayout_2;
  QLineEdit *searchLine;
  QToolBox *searchResultToolbox;
  QListWidget *searchResultArtists;
  QListWidget *searchResultPlaylists;
  QListWidget *searchResultTracks;
  QWidget *filesTab;
  QGridLayout *gridLayout_2;
  QScrollArea *playlistScroll;
  QWidget *playlistScrollContent;
  QHBoxLayout *horizontalLayout_3;

  QStringList searchCompleteWordList;
  QCompleter *completer;

  Playlist generatedFromTracksPlaylist;

  void setupUi() {
    if (this->objectName().isEmpty())
      this->setObjectName(QString::fromUtf8("Finder"));
    this->resize(405, 205);
    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    tab = new QTabWidget(this);
    tab->setObjectName(QString::fromUtf8("tab"));
    tab->setTabShape(QTabWidget::Rounded);
    searchTab = new QWidget();
    searchTab->setObjectName(QString::fromUtf8("searchTab"));
    verticalLayout_2 = new QVBoxLayout(searchTab);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

    completer = new QCompleter(searchCompleteWordList, this);
    searchCompleteWordList << "SQL "
                           << "HTTP://";
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(new QStandardItemModel(completer));

    searchLine = new QLineEdit(searchTab);
    searchLine->setObjectName(QString::fromUtf8("searchLine"));
    searchLine->setCompleter(completer);

    verticalLayout_2->addWidget(searchLine);

    searchResultToolbox = new QToolBox(searchTab);

    searchResultArtists = new QListWidget(searchTab);
    searchResultArtists->setObjectName(QString::fromUtf8("searchResult"));
    searchResultToolbox->addItem(searchResultArtists, "Artists");

    searchResultPlaylists = new QListWidget(searchTab);
    searchResultPlaylists->setObjectName(QString::fromUtf8("searchResult"));
    searchResultToolbox->addItem(searchResultPlaylists, "Playlists");

    searchResultTracks = new QListWidget(searchTab);
    searchResultTracks->setObjectName(QString::fromUtf8("searchResult"));
    searchResultToolbox->addItem(searchResultTracks, "Tracks");

    verticalLayout_2->addWidget(searchResultToolbox);

    tab->addTab(searchTab, QString());
    filesTab = new QWidget();
    filesTab->setObjectName(QString::fromUtf8("filesTab"));
    gridLayout_2 = new QGridLayout(filesTab);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    playlistScroll = new QScrollArea(filesTab);
    playlistScroll->setObjectName(QString::fromUtf8("playlistScroll"));
    playlistScroll->setWidgetResizable(true);
    playlistScrollContent = new QWidget();
    playlistScrollContent->setObjectName(
        QString::fromUtf8("playlistScrollContent"));
    playlistScrollContent->setGeometry(QRect(0, 0, 381, 154));
    horizontalLayout_3 = new QHBoxLayout(playlistScrollContent);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    playlistScroll->setWidget(playlistScrollContent);

    gridLayout_2->addWidget(playlistScroll, 0, 0, 1, 1);

    tab->addTab(filesTab, QString());

    gridLayout->addWidget(tab, 0, 0, 1, 1);

    retranslateUi();

    tab->setCurrentIndex(1);

    connect(searchLine, &QLineEdit::returnPressed, this, &Finder::onSearch);

    QMetaObject::connectSlotsByName(this);
  } // setupUi

  void retranslateUi() {
    this->setWindowTitle(
        QCoreApplication::translate("Finder", "Form", nullptr));
    searchLine->setPlaceholderText(QCoreApplication::translate(
        "Finder", "Query / artist / album / track / filename / playlist",
        nullptr));
    tab->setTabText(tab->indexOf(searchTab),
                    QCoreApplication::translate("Finder", "Search", nullptr));
    tab->setTabText(
        tab->indexOf(filesTab),
        QCoreApplication::translate("Finder", "Playlists", nullptr));
  } // retranslateUi
  Finder() {}
  Playlist getHoldedPlaylist(){
    return generatedFromTracksPlaylist;
  }
  void onSearch() {
    
    Library::fuzzySearchOutput searchResult =
        Library::fuzzySearch(searchLine->text().toStdString());
    
/*
    for (Source source : searchResult.playlists) {
      cout << "playlist: " << source.path << endl;
    }
    for (Source source : searchResult.tracks) {
      cout << "track: " << source.path << endl;
    }
    for (string artist : searchResult.artists) {
      cout << "artist: " << artist << endl;
    }
    */
    searchResultArtists->clear();
    searchResultPlaylists->clear();
    searchResultTracks->clear();
    
    /*
    qDeleteAll(searchResultArtists->findChildren<QWidget *>(
        "", Qt::FindDirectChildrenOnly));
    qDeleteAll(searchResultPlaylists->findChildren<QWidget *>(
        "", Qt::FindDirectChildrenOnly));
    qDeleteAll(searchResultTracks->findChildren<QWidget *>(
        "", Qt::FindDirectChildrenOnly));
    */
    // make found tracks playlist
    
    generatedFromTracksPlaylist.tracks = {};
    generatedFromTracksPlaylist.name = "search_"+to_string(time_ms());
    for (Source trackSource : searchResult.tracks) {
      Track track(trackSource);
      track = client.assembleTrack(track);
      generatedFromTracksPlaylist.tracks.push_back(track);
    }
    
    int index = 0;
    for (Track track : generatedFromTracksPlaylist.tracks) {
      TrackLine *trackLine = new TrackLine();
      trackLine->setPlaylistHolder(this);
      trackLine->setupUi();
      trackLine->setTrack(track, generatedFromTracksPlaylist, index);

      QListWidgetItem *widgetItem = new QListWidgetItem();

      searchResultTracks->addItem(widgetItem);
      searchResultTracks->setItemWidget(widgetItem, trackLine);
      widgetItem->setSizeHint(trackLine->sizeHint());
      index++;
    }
    
    for (Source playlistSource : searchResult.playlists){
      PlaylistLine *playlistLine = new PlaylistLine();
      
      playlistLine->setupUi();
      playlistLine->setPlaylist(playlistSource);
      
      QListWidgetItem *widgetItem = new QListWidgetItem();
      searchResultPlaylists->addItem(widgetItem);
      searchResultPlaylists->setItemWidget(widgetItem, playlistLine);
      widgetItem->setSizeHint(playlistLine->sizeHint());
    }

    // change style of toolbox
    searchResultToolbox->setItemEnabled(0, searchResult.artists.size() != 0);
    searchResultToolbox->setItemEnabled(1, searchResult.playlists.size() != 0);
    searchResultToolbox->setItemEnabled(2, searchResult.tracks.size() != 0);

    stringstream artistsToolboxText;
    artistsToolboxText << "Artists (" << searchResult.artists.size() << ")";
    searchResultToolbox->setItemText(0,
    QString::fromStdString(artistsToolboxText.str())
    );
        stringstream playlistsToolboxText;
    playlistsToolboxText << "Playlists (" << searchResult.playlists.size() << ")";
    searchResultToolbox->setItemText(1,
    QString::fromStdString(playlistsToolboxText.str())
    );
        stringstream tracksToolboxText;
    tracksToolboxText << "Tracks (" << searchResult.tracks.size() << ")";
    searchResultToolbox->setItemText(2,
    QString::fromStdString(tracksToolboxText.str())
    );
  }
};

#endif // FINDER_H

#ifndef TRACKLINE_H
#define TRACKLINE_H

#include "globals.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>
#include <iostream>

#include "../../Data.hpp"
#include "../../StandartGlobalUser.hpp"
#include "../../macro.hpp"
#include "../ui.hpp"
#include "Modals.h"

using namespace std;

class PlaylistHolder {
public:
  virtual Playlist getHoldedPlaylist(){};
};

class TrackLine : public virtual StandartGlobalUser, public QWidget {
public:
  QHBoxLayout *horizontalLayout;
  QVBoxLayout *verticalLayout;
  QSpacerItem *verticalSpacer;
  QPushButton *playButton;
  QLabel *durationLabel;
  QSpacerItem *verticalSpacer_3;
  QVBoxLayout *verticalLayout_2;
  QLabel *titleLabel;
  QHBoxLayout *horizontalLayout_3;
  QLabel *artistsLabel;
  QSpacerItem *horizontalSpacer;
  QLabel *albumLabel;
  QLabel *filenameLabel;
  QSpacerItem *horizontalSpacer_2;
  QHBoxLayout *horizontalLayout_2;
  QPushButton *extraButton;

  TrackActionsModal *modal;

  int indexInPlaylist = -1;
  PlaylistHolder *holder;
  bool setup = false;

  void setupUi() {
    if (this->objectName().isEmpty())
      this->setObjectName(QString::fromUtf8("form"));
    this->resize(669, 82);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(3, 3, 3, 3);
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalSpacer =
        new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    playButton = new QPushButton(this);
    playButton->setObjectName(QString::fromUtf8("playButton"));
    playButton->setEnabled(true);
    playButton->setMinimumSize(QSize(35, 35));
    playButton->setMaximumSize(QSize(35, 35));

    verticalLayout->addWidget(playButton);

    durationLabel = new QLabel(this);
    durationLabel->setObjectName(QString::fromUtf8("durationLabel"));
    durationLabel->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(durationLabel);

    verticalSpacer_3 =
        new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_3);

    horizontalLayout->addLayout(verticalLayout);

    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    titleLabel = new QLabel(this);
    titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
    titleLabel->setSizePolicy(sizePolicy1);
    QFont font;
    font.setPointSize(14);
    font.setBold(false);
    font.setWeight(50);
    titleLabel->setFont(font);
    titleLabel->setCursor(QCursor(Qt::UpArrowCursor));
    titleLabel->setLayoutDirection(Qt::LeftToRight);
    titleLabel->setAutoFillBackground(false);
    titleLabel->setScaledContents(false);
    titleLabel->setWordWrap(true);
    titleLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse |
                                        Qt::TextSelectableByMouse);

    verticalLayout_2->addWidget(titleLabel);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    artistsLabel = new QLabel(this);
    artistsLabel->setObjectName(QString::fromUtf8("artistsLabel"));
    QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(
        artistsLabel->sizePolicy().hasHeightForWidth());
    artistsLabel->setSizePolicy(sizePolicy2);
    artistsLabel->setWordWrap(true);
    QFont font1;
    font1.setKerning(true);
    font1.setPointSize(10);
    artistsLabel->setFont(font1);

    horizontalLayout_3->addWidget(artistsLabel);

    horizontalSpacer =
        new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer);

    albumLabel = new QLabel(this);
    albumLabel->setObjectName(QString::fromUtf8("albumLabel"));
    albumLabel->setWordWrap(true);
    sizePolicy2.setHeightForWidth(albumLabel->sizePolicy().hasHeightForWidth());
    albumLabel->setSizePolicy(sizePolicy2);
    albumLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse |
                                        Qt::TextSelectableByMouse);

    horizontalLayout_3->addWidget(albumLabel);

    verticalLayout_2->addLayout(horizontalLayout_3);

    filenameLabel = new QLabel(this);
    filenameLabel->setObjectName(QString::fromUtf8("filenameLabel"));
    sizePolicy1.setHeightForWidth(
        filenameLabel->sizePolicy().hasHeightForWidth());
    filenameLabel->setSizePolicy(sizePolicy1);
    filenameLabel->setWordWrap(true);
    QFont font2;
    font2.setPointSize(8);
    filenameLabel->setFont(font2);
    filenameLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse |
                                           Qt::TextSelectableByMouse);

    verticalLayout_2->addWidget(filenameLabel);

    horizontalLayout->addLayout(verticalLayout_2);

    horizontalSpacer_2 =
        new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer_2);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
    extraButton = new QPushButton(this);
    extraButton->setIcon(QIcon(QString::fromStdString(Icons::MOREVERT)));
    extraButton->setObjectName(QString::fromUtf8("extraButton"));
    extraButton->setMaximumSize(QSize(30, 30));

    horizontalLayout_2->addWidget(extraButton);

    horizontalLayout->addLayout(horizontalLayout_2);

    this->connect(playButton, &QPushButton::pressed, this,
                  &TrackLine::onPlayPressed);
    this->connect(extraButton, &QPushButton::pressed, this,
                  &TrackLine::onExtraPressed);

    // retranslateUi(this);

    QMetaObject::connectSlotsByName(this);
    setup = true;
  } // setupUi

  void retranslateUi(QWidget *Form) {
    /*
    Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
    playButton->setText(QString());
    durationLabel->setText(
        QCoreApplication::translate("Form", "04:20", nullptr));
    titleLabel->setText(QCoreApplication::translate("Form", "Title", nullptr));
    artistsLabel->setText(
        QCoreApplication::translate("Form", "Artists", nullptr));
    albumLabel->setText(QCoreApplication::translate("Form", "Album", nullptr));
    filenameLabel->setText(
        QCoreApplication::translate("Form", "Filename", nullptr));
    extraButton->setText(QString());
    */
  } // retranslateUi
  void setPlaylistHolder(PlaylistHolder *_holder) { holder = _holder; }
  void setTrack(Track track, Playlist _playlist, int index = -1) {

    indexInPlaylist = index;
    titleLabel->setText(QString::fromStdString(track.title));
    albumLabel->setText(QString::fromStdString(track.album));
    artistsLabel->setText(QString::fromStdString(track.artists));
    filenameLabel->setText(QString::fromStdString(track.filename));
    durationLabel->setText(
        QString::fromStdString(secondsToTime(track.duration)));

    if (soundmaker.getTrack().filename == track.filename and
        soundmaker.getIsPlaying()) {
      playButton->setIcon(QIcon(QString::fromStdString(Icons::PAUSE)));
    } else {
      playButton->setIcon(QIcon(QString::fromStdString(Icons::PLAY)));
    }
  }
  void onPlayPressed() {
    
    if (holder) {
      Playlist parentPlaylist = holder->getHoldedPlaylist();
      Track track = parentPlaylist.tracks[indexInPlaylist];
      if (soundmaker.getCurrentPlaylist().name != parentPlaylist.name) {
        soundmaker.setPlaylist(parentPlaylist, indexInPlaylist);
        soundmaker.play();
        return;
      }
      if (soundmaker.getTrack().filename == track.filename) {
        if (soundmaker.getIsPlaying()) {
          soundmaker.pause();
        } else {
          soundmaker.play();
        }

      } else {
        soundmaker.setCurrentIndex(indexInPlaylist);
        soundmaker.play();
      }
    }
  }
  void onExtraPressed() {
    Playlist parentPlaylist = holder->getHoldedPlaylist();
    Track track = parentPlaylist.tracks[indexInPlaylist];
    if (modal) {
      delete modal;
    }
    modal = new TrackActionsModal();

    modal->setup(track);
    QPoint globalCursorPos = QCursor::pos();
    modal->setGeometry(globalCursorPos.x(), globalCursorPos.y(),
                       modal->geometry().x(), modal->geometry().y());
    modal->show();
  }
  // update existence in playlists, load state
  void updateRelation(bool isInFAvourite, bool isDownloaded) {
    if (isDownloaded) {
    }

    if (isInFAvourite) {
    }
  }
  void onMediaChanged() {
    Playlist parentPlaylist = holder->getHoldedPlaylist();
    if (indexInPlaylist>=parentPlaylist.size()){
      return;
    }
    Track track = parentPlaylist.tracks[indexInPlaylist];
    if (soundmaker.getTrack().filename == track.filename and
        soundmaker.getIsPlaying()) {
      playButton->setIcon(QIcon(QString::fromStdString(Icons::PAUSE)));
    } else {
      playButton->setIcon(QIcon(QString::fromStdString(Icons::PLAY)));
    }
  }


  void eventProcessor(const Types::Event &event) {
    switch (event) {
    case Types::Event::onMediaPlayerMediaChanged:
      onMediaChanged();
      break;
    case Types::Event::onMediaPlayerPlaying:
      eventProcessor(Types::Event::onMediaPlayerMediaChanged);
      break;
    case Types::Event::onMediaPlayerPaused:
      eventProcessor(Types::Event::onMediaPlayerMediaChanged);
      break;
    case Types::Event::FILES_UPDATED:
      break;
    default:
      break;
    }
  }
};

#endif

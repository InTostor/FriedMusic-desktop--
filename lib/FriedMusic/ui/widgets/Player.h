/********************************************************************************
** Form generated from reading UI file 'playerWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include "Library.hpp"
#include <QApplication>
#include <QAudio>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>
#include <iostream>

#include "../../StandartGlobalUser.hpp"
#include "../ui.hpp"

class Player : public virtual StandartGlobalUser, public QWidget {
public:
  QHBoxLayout *horizontalLayout;
  QVBoxLayout *playerMainControlsLayout;
  QLabel *infoTrack;
  QHBoxLayout *artistInfoLayout;
  QLabel *infoArtist;
  QLabel *infoAlbum;
  QLabel *infoFilename;
  QHBoxLayout *playerMainButtons;
  QPushButton *prevButton;
  QPushButton *playButton;
  QPushButton *nextButton;
  QHBoxLayout *seekerLayout;
  QLabel *seekerLabel;
  QSlider *seekerSlider;
  QHBoxLayout *auxButtonLayout;
  QComboBox *loopComboBox;
  QPushButton *shuffleButton;
  QPushButton *addToFavouriteButton;
  QPushButton *downloadButton;
  QPushButton *addToPlaylistButton;
  QSpacerItem *horizontalSpacer;
  QHBoxLayout *horizontalLayout_2;
  QPushButton *setDynamicPlaylistButton;
  QPushButton *customizeDynamicPlaylistButton;
  QVBoxLayout *volumeLayout;
  QSlider *volumeSlider;
  QLabel *volumeLabel;
  QMap<QString, Types::Loop> *loopModesQEnum = new QMap<QString, Types::Loop>;

  void setupUi() {
    if (this->QWidget::objectName().isEmpty())
      this->QWidget::setObjectName(QString::fromUtf8("Form"));
    this->setEnabled(true);
    this->resize(400, 200);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(QSize(200, 200));
    this->setMaximumSize(QSize(960, 200));
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    playerMainControlsLayout = new QVBoxLayout();
    playerMainControlsLayout->setObjectName(
        QString::fromUtf8("playerMainControlsLayout"));
    infoTrack = new QLabel(this);
    infoTrack->setObjectName(QString::fromUtf8("infoTrack"));
    QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding,
                            QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(infoTrack->sizePolicy().hasHeightForWidth());
    infoTrack->setSizePolicy(sizePolicy1);
    QFont font;
    font.setPointSize(16);
    infoTrack->setFont(font);
    infoTrack->setWordWrap(true);
    infoTrack->setTextInteractionFlags(Qt::LinksAccessibleByMouse |
                                       Qt::TextSelectableByMouse);

    playerMainControlsLayout->addWidget(infoTrack);

    artistInfoLayout = new QHBoxLayout();
    artistInfoLayout->setObjectName(QString::fromUtf8("artistInfoLayout"));
    infoArtist = new QLabel(this);
    infoArtist->setObjectName(QString::fromUtf8("infoArtist"));
    QFont font1;
    font1.setPointSize(12);
    infoArtist->setFont(font1);
    infoArtist->setWordWrap(true);
    infoArtist->setTextInteractionFlags(Qt::LinksAccessibleByMouse |
                                        Qt::TextSelectableByMouse);

    artistInfoLayout->addWidget(infoArtist);

    infoAlbum = new QLabel(this);
    infoAlbum->setObjectName(QString::fromUtf8("infoAlbum"));
    infoAlbum->setFont(font1);
    infoAlbum->setAlignment(Qt::AlignRight | Qt::AlignTrailing |
                            Qt::AlignVCenter);
    infoAlbum->setWordWrap(true);
    infoAlbum->setTextInteractionFlags(Qt::LinksAccessibleByMouse |
                                       Qt::TextSelectableByMouse);

    artistInfoLayout->addWidget(infoAlbum);

    playerMainControlsLayout->addLayout(artistInfoLayout);

    infoFilename = new QLabel(this);
    infoFilename->setObjectName(QString::fromUtf8("infoFilename"));
    sizePolicy1.setHeightForWidth(
        infoFilename->sizePolicy().hasHeightForWidth());
    infoFilename->setSizePolicy(sizePolicy1);
    QFont font2;
    font2.setPointSize(7);
    infoFilename->setFont(font2);
    infoFilename->setWordWrap(true);
    infoFilename->setTextInteractionFlags(Qt::LinksAccessibleByMouse |
                                          Qt::TextSelectableByMouse);

    playerMainControlsLayout->addWidget(infoFilename);

    playerMainButtons = new QHBoxLayout();
    playerMainButtons->setObjectName(QString::fromUtf8("playerMainButtons"));
    prevButton = new QPushButton(this);
    prevButton->setObjectName(QString::fromUtf8("prevButton"));
    prevButton->setMinimumSize(QSize(0, 0));
    prevButton->setMaximumSize(QSize(50, 50));
    prevButton->setToolTip("Previous track");

    playerMainButtons->addWidget(prevButton);

    playButton = new QPushButton(this);
    playButton->setObjectName(QString::fromUtf8("playButton"));
    playButton->setMinimumSize(QSize(0, 0));
    playButton->setMaximumSize(QSize(50, 50));
    playButton->setAutoFillBackground(false);
    playButton->setToolTip("Play/pause");

    playerMainButtons->addWidget(playButton);

    nextButton = new QPushButton(this);
    nextButton->setObjectName(QString::fromUtf8("nextButton"));
    nextButton->setMinimumSize(QSize(0, 0));
    nextButton->setMaximumSize(QSize(50, 50));
    nextButton->setToolTip("Next track");

    playerMainButtons->addWidget(nextButton);

    playerMainControlsLayout->addLayout(playerMainButtons);

    seekerLayout = new QHBoxLayout();
    seekerLayout->setObjectName(QString::fromUtf8("seekerLayout"));
    seekerLabel = new QLabel(this);
    seekerLabel->setObjectName(QString::fromUtf8("seekerLabel"));
    seekerLabel->setMaximumSize(QSize(16777215, 50));

    seekerLayout->addWidget(seekerLabel);

    seekerSlider = new QSlider(this);
    seekerSlider->setObjectName(QString::fromUtf8("seekerSlider"));
    seekerSlider->setMaximum(200);
    seekerSlider->setOrientation(Qt::Horizontal);
    seekerSlider->setTickPosition(QSlider::NoTicks);

    seekerLayout->addWidget(seekerSlider);

    playerMainControlsLayout->addLayout(seekerLayout);

    auxButtonLayout = new QHBoxLayout();
    auxButtonLayout->setObjectName(QString::fromUtf8("auxButtonLayout"));
    loopComboBox = new QComboBox(this);
    loopComboBox->setObjectName(QString::fromUtf8("loopComboBox"));
    loopComboBox->setMaximumSize(QSize(100, 16777215));

    auxButtonLayout->addWidget(loopComboBox);

    shuffleButton = new QPushButton(this);
    shuffleButton->setObjectName(QString::fromUtf8("shuffleButton"));
    shuffleButton->setMinimumSize(QSize(35, 35));
    shuffleButton->setMaximumSize(QSize(35, 35));

    auxButtonLayout->addWidget(shuffleButton);

    addToFavouriteButton = new QPushButton(this);
    addToFavouriteButton->setObjectName(
        QString::fromUtf8("addToFavouriteButton"));
    addToFavouriteButton->setMinimumSize(QSize(35, 35));
    addToFavouriteButton->setMaximumSize(QSize(35, 35));

    downloadButton = new QPushButton(this);
    downloadButton->setObjectName(QString::fromUtf8("downloadButton"));
    downloadButton->setMinimumSize(QSize(35, 35));
    downloadButton->setMaximumSize(QSize(35, 35));

    auxButtonLayout->addWidget(addToFavouriteButton);
    auxButtonLayout->addWidget(downloadButton);

    addToPlaylistButton = new QPushButton(this);
    addToPlaylistButton->setObjectName(
        QString::fromUtf8("addToPlaylistButton"));
    addToPlaylistButton->setMinimumSize(QSize(35, 35));
    addToPlaylistButton->setMaximumSize(QSize(35, 35));

    auxButtonLayout->addWidget(addToPlaylistButton);

    horizontalSpacer =
        new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    auxButtonLayout->addItem(horizontalSpacer);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    setDynamicPlaylistButton = new QPushButton(this);
    setDynamicPlaylistButton->setText("Dynamic");
    setDynamicPlaylistButton->setObjectName(
        QString::fromUtf8("setDynamicPlaylistButton"));
    setDynamicPlaylistButton->setMaximumSize(QSize(70, 35));
    setDynamicPlaylistButton->setMinimumSize(QSize(70, 35));

    horizontalLayout_2->addWidget(setDynamicPlaylistButton);

    customizeDynamicPlaylistButton = new QPushButton(this);
    customizeDynamicPlaylistButton->setObjectName(
        QString::fromUtf8("customizeDynamicPlaylistButton"));
    customizeDynamicPlaylistButton->setMaximumSize(QSize(35, 35));
    customizeDynamicPlaylistButton->setMinimumSize(QSize(35, 35));

    horizontalLayout_2->addWidget(customizeDynamicPlaylistButton);

    auxButtonLayout->addLayout(horizontalLayout_2);

    playerMainControlsLayout->addLayout(auxButtonLayout);

    horizontalLayout->addLayout(playerMainControlsLayout);

    volumeLayout = new QVBoxLayout();
    volumeLayout->setObjectName(QString::fromUtf8("volumeLayout"));
    volumeLayout->setSizeConstraint(QLayout::SetMinimumSize);
    volumeSlider = new QSlider(this);
    volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
    volumeSlider->setMaximum(101);
    volumeSlider->setOrientation(Qt::Vertical);
    volumeSlider->setTickPosition(QSlider::TicksBelow);

    volumeLayout->addWidget(volumeSlider, 0, Qt::AlignRight);

    volumeLabel = new QLabel(this);
    volumeLabel->setObjectName(QString::fromUtf8("volumeLabel"));
    volumeLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing |
                              Qt::AlignVCenter);
    volumeLabel->setMinimumSize(QSize(50, 0));
    volumeLayout->addWidget(volumeLabel, 0, Qt::AlignRight);

    horizontalLayout->addLayout(volumeLayout);

    // Icons setup
    prevButton->setIcon(QIcon(QString::fromStdString(Icons::PREV)));
    nextButton->setIcon(QIcon(QString::fromStdString(Icons::NEXT)));
    playButton->setIcon(QIcon(QString::fromStdString(Icons::PLAY)));

    loopModesQEnum->insert("None", Types::Loop::NONE);
    loopModesQEnum->insert("Track once", Types::Loop::TRACKONCE);
    loopModesQEnum->insert("Track", Types::Loop::TRACK);
    loopModesQEnum->insert("Playlist once", Types::Loop::PLAYLISTONCE);
    loopModesQEnum->insert("Playlist", Types::Loop::PLAYLIST);
    loopComboBox->addItems(QStringList(loopModesQEnum->keys()));

    addToPlaylistButton->setIcon(QIcon(QString::fromStdString(Icons::TOLIST)));
    addToFavouriteButton->setIcon(
        QIcon(QString::fromStdString(Icons::TOFAVOURITE)));
    shuffleButton->setIcon(QIcon(QString::fromStdString(Icons::SHUFFLE)));

    // Button actions connection
    this->QWidget::connect(seekerSlider, &QSlider::sliderMoved, this,
                           &Player::onSeekerMoved);
    this->QWidget::connect(volumeSlider, &QSlider::sliderMoved, this,
                           &Player::onVolumeMoved);
    this->QWidget::connect(playButton, &QPushButton::pressed, this,
                           &Player::onPlayPressed);
    this->QWidget::connect(nextButton, &QPushButton::pressed, this,
                           &Player::onNextPressed);
    this->QWidget::connect(prevButton, &QPushButton::pressed, this,
                           &Player::onPrevPressed);
    this->QWidget::connect(shuffleButton, &QPushButton::pressed, this,
                           &Player::onShufflePressed);
    this->QWidget::connect(addToFavouriteButton, &QPushButton::pressed, this,
                           &Player::onToFavouritePressed);
    this->QWidget::connect(addToPlaylistButton, &QPushButton::pressed, this,
                           &Player::onToPlaylistPressed);
    this->QWidget::connect(downloadButton, &QPushButton::pressed, this,
                           &Player::onDownloadPressed);
    this->QWidget::connect(loopComboBox, &QComboBox::currentTextChanged, this,
                           &Player::onLoopComboboxSelected);
    this->QWidget::connect(setDynamicPlaylistButton, &QPushButton::pressed,
                           this, &Player::onDynamicPlaylistPressed);

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
  } // setupUi

  void retranslateUi() {
    this->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
    infoTrack->setText(QCoreApplication::translate("Form", "Track", nullptr));
    infoArtist->setText(QCoreApplication::translate("Form", "Artist", nullptr));
    infoAlbum->setText(QCoreApplication::translate("Form", "Album", nullptr));
    infoFilename->setText(
        QCoreApplication::translate("Form", "Filename", nullptr));
    prevButton->setText(QString());
    prevButton->setProperty("class",
                            QVariant(QCoreApplication::translate(
                                "Form", "squareButtonMedium", nullptr)));
    playButton->setText(QString());
    playButton->setProperty("class",
                            QVariant(QCoreApplication::translate(
                                "Form", "squareButtonMedium", nullptr)));
    nextButton->setText(QString());
    nextButton->setProperty("class",
                            QVariant(QCoreApplication::translate(
                                "Form", "squareButtonMedium", nullptr)));
    seekerLabel->setText(QCoreApplication::translate("Form", "04:20", nullptr));
    shuffleButton->setText(QString());
    shuffleButton->setProperty("class",
                               QVariant(QCoreApplication::translate(
                                   "Form", "squareButtonSmall", nullptr)));
    addToFavouriteButton->setText(QString());
    addToFavouriteButton->setProperty(
        "class", QVariant(QCoreApplication::translate(
                     "Form", "squareButtonSmall", nullptr)));
    addToPlaylistButton->setText(QString());
    addToPlaylistButton->setProperty(
        "class", QVariant(QCoreApplication::translate(
                     "Form", "squareButtonSmall", nullptr)));
    volumeLabel->setText(QCoreApplication::translate("Form", "100%", nullptr));
  } // retranslateUi

  // Player() {}
  void onMediaPlayerMediaChanged() {
    Track currentTrack = soundmaker->getTrack();
    try {
      infoArtist->setText(QString::fromStdString(currentTrack.artists));
      infoAlbum->setText(QString::fromStdString(currentTrack.album));
      infoTrack->setText(QString::fromStdString(currentTrack.title));
      infoFilename->setText(QString::fromStdString(currentTrack.filename));
    } catch (...) {
      // i don't care
    }
  }
  void onMediaPlayerPositionChanged() {
    seekerLabel->setText(
        QString::fromStdString(secondsToTime(soundmaker->getTime() / 1000.0)));
    if (!seekerSlider->isSliderDown()) {
      seekerSlider->setValue(
          (int)(seekerSlider->maximum() * soundmaker->getPosition()));
    }
  }
  void onMediaPlayerPlaying() {
    playButton->setIcon(QIcon(QString::fromStdString(Icons::PAUSE)));
  }
  void onMediaPlayerPaused() {
    playButton->setIcon(QIcon(QString::fromStdString(Icons::PLAY)));
  }
  void onPlayPressed() {
    if (soundmaker->getIsPlaying()) {
      soundmaker->pause();
    } else {
      soundmaker->play();
    }
  }
  void onNextPressed() { soundmaker->next(); }
  void onPrevPressed() { soundmaker->previous(); }
  void onSeekerMoved() {
    soundmaker->setPosition(seekerSlider->value() /
                           (float)seekerSlider->maximum());
  }
  void onDynamicPlaylistPressed() {
    if (soundmaker->getCurrentPlaylist().name != "dynamic"){
      MainGeneratorPlaylist *dynamic = new MainGeneratorPlaylist();
      soundmaker->setPlaylist(dynamic);
      soundmaker->play();
    }
  }
  void onVolumeMoved() {
    // logarithmic
    /*
    qreal logarithmicVolume = QAudio::convertVolume(
        volumeSlider->value() / qreal(100), QAudio::LinearVolumeScale,
        QAudio::LogarithmicVolumeScale);
    soundmaker->player->setVolume((int)(logarithmicVolume * 100));
    */
    // linear
    soundmaker->player->setVolume(volumeSlider->value());

    string txt = std::to_string(volumeSlider->value()) + "%";
    volumeLabel->setText(QString::fromStdString(txt));
  }
  void onShufflePressed() {}
  void onToFavouritePressed() {
    Track currentTrack = soundmaker->getTrack();
    Source favourite = Library::getPlaylistSource("favourite.fpl");
    Playlist favouritePlaylist = client.getPlaylistFromSource(favourite);
    if (client.isTrackInPlaylist(currentTrack, favourite)) {
      vector<Track>::iterator it = std::find_if(
          favouritePlaylist.tracks.begin(), favouritePlaylist.tracks.end(),
          [&](Track const &t) { return t.filename == currentTrack.filename; });
      favouritePlaylist.tracks.erase(it);
    } else {
      favouritePlaylist.tracks.push_back(currentTrack);
    }
    Library::savePlaylistLocally(favouritePlaylist);
  }
  void onDownloadPressed() {
    Track currentTrack = soundmaker->getTrack();
    Types::StorageType existence = Library::isSourceExists(currentTrack.source);
    if (existence == Types::StorageType::LOCAL ||
        existence == Types::StorageType::ANY) {
      Library::deleteTrack(currentTrack);
    } else {
      client.downloadTrack(currentTrack.filename);
    }
  }
  void onToPlaylistPressed() {}
  void onLoopComboboxSelected() {
    soundmaker->setLoopMode(loopModesQEnum->value(loopComboBox->currentText()));
  }
  void onFilesUpdated() {
    Source favourite = Library::getPlaylistSource("favourite.fpl");
    Playlist favouritePlaylist = client.getPlaylistFromSource(favourite);
    Track currentTrack = soundmaker->getTrack();
    if (client.isTrackInPlaylist(currentTrack, favourite)) {
      addToFavouriteButton->setIcon(
          QIcon(QString::fromStdString(Icons::UNFAVOURITE)));
    } else {
      addToFavouriteButton->setIcon(
          QIcon(QString::fromStdString(Icons::TOFAVOURITE)));
    }
    if (client.isTrackDownloaded(currentTrack)) {
      downloadButton->setIcon(QIcon(QString::fromStdString(Icons::DELETE)));
    } else {
      downloadButton->setIcon(QIcon(QString::fromStdString(Icons::DOWNLOAD)));
    }
  }
  void eventProcessor(const Types::Event &event) {
    switch (event) {
    case Types::Event::onMediaPlayerMediaChanged:
      onMediaPlayerMediaChanged();
      onFilesUpdated();
      break;
    case Types::Event::onMediaPlayerPositionChanged:
      onMediaPlayerPositionChanged();
      break;
    case Types::Event::onMediaPlayerPlaying:
      onMediaPlayerPlaying();
      break;
    case Types::Event::onMediaPlayerPaused:
      onMediaPlayerPaused();
      break;
    case Types::Event::onMediaPlayerStopped:
      onMediaPlayerPaused();
      break;
    case Types::Event::onMediaPlayerMediaFinished:

      if (soundmaker->getIsPlaying()) {
        playButton->setIcon(QIcon(QString::fromStdString(Icons::PAUSE)));
      } else {
        playButton->setIcon(QIcon(QString::fromStdString(Icons::PLAY)));
      }
      break;
    case Types::Event::onMediaPlayerLoopModeChanged:
      loopComboBox->setCurrentText(
          loopModesQEnum->key(soundmaker->getLoopMode()));
      break;
    case Types::Event::FILES_UPDATED:
      onFilesUpdated();
      break;
    default:
      break;
    }
  }
};

#endif // PLAYERWIDGET_H

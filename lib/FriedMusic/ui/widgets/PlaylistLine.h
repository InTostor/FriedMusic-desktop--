#ifndef PLAYLISTLINEGIFUZE_H
#define PLAYLISTLINEGIFUZE_H

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>
#include <qpushbutton.h>

#include "Data.hpp"
#include "StandartGlobalUser.hpp"

class PlaylistLine : public QWidget, public StandartGlobalUser {
public:
  QHBoxLayout *horizontalLayout;
  QVBoxLayout *verticalLayout;
  QSpacerItem *verticalSpacer;
  QPushButton *playButton;
  QLabel *durationLabel;
  QSpacerItem *verticalSpacer_3;
  QVBoxLayout *verticalLayout_2;
  QLabel *nameLabel;
  QLabel *filenameLabel;
  QSpacerItem *horizontalSpacer_2;
  QHBoxLayout *horizontalLayout_2;
  QPushButton *extraButton;

  Source _playlistSource;

  void setupUi() {
    if (this->objectName().isEmpty())
      this->setObjectName(QString::fromUtf8("Form"));
    this->resize(297, 130);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
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
    nameLabel = new QLabel(this);
    nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(nameLabel->sizePolicy().hasHeightForWidth());
    nameLabel->setSizePolicy(sizePolicy1);
    QFont font;
    font.setPointSize(14);
    font.setBold(false);
    font.setWeight(50);
    nameLabel->setFont(font);
    nameLabel->setCursor(QCursor(Qt::UpArrowCursor));
    nameLabel->setLayoutDirection(Qt::LeftToRight);
    nameLabel->setAutoFillBackground(false);
    nameLabel->setScaledContents(false);
    nameLabel->setWordWrap(true);
    nameLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse |
                                       Qt::TextSelectableByMouse);

    verticalLayout_2->addWidget(nameLabel);

    filenameLabel = new QLabel(this);
    filenameLabel->setObjectName(QString::fromUtf8("filenameLabel"));
    sizePolicy1.setHeightForWidth(
        filenameLabel->sizePolicy().hasHeightForWidth());
    filenameLabel->setSizePolicy(sizePolicy1);
    QFont font1;
    font1.setPointSize(10);
    filenameLabel->setFont(font1);

    verticalLayout_2->addWidget(filenameLabel);

    horizontalLayout->addLayout(verticalLayout_2);

    horizontalSpacer_2 = new QSpacerItem(10, 10, QSizePolicy::MinimumExpanding,
                                         QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer_2);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
    extraButton = new QPushButton(this);
    extraButton->setIcon(QIcon(QString::fromStdString(Icons::MOREVERT)));
    extraButton->setObjectName(QString::fromUtf8("extraButton"));
    extraButton->setMaximumSize(QSize(35, 35));

    horizontalLayout_2->addWidget(extraButton);

    horizontalLayout->addLayout(horizontalLayout_2);

    connect(playButton,&QPushButton::pressed,this,&PlaylistLine::onPlayPressed);

    onPlaylistChanged();

    QMetaObject::connectSlotsByName(this);
  } // setupUi
  void setPlaylist(Source playlistSource) {
    _playlistSource = playlistSource;
    nameLabel->setText(QString::fromStdString(_playlistSource.path));
  }
  void onPlayPressed() {
    if (soundmaker.getCurrentPlaylist().name !=
        std::filesystem::path(_playlistSource.path).filename()) {
      soundmaker.setPlaylist(_playlistSource);
      soundmaker.setCurrentIndex(0);
      soundmaker.play();
      return;
    }else{
      if (soundmaker.getIsPlaying()){
        soundmaker.play();
      }else{
        soundmaker.pause();
      }
    }
  }
  void onExtraPressed() {
    PlaylistActionsModal *modal = new PlaylistActionsModal();
    
    modal->setup(_playlistSource);
    QPoint globalCursorPos = QCursor::pos();
    modal->setGeometry(globalCursorPos.x(), globalCursorPos.y(),
                       modal->geometry().x(), modal->geometry().y());
    modal->show();
  }
  void onPlaylistChanged() {
    if (soundmaker.getCurrentPlaylist().name ==
        std::filesystem::path(_playlistSource.path).filename() and soundmaker.getIsPlaying()) {
      playButton->setIcon(QIcon(QString::fromStdString(Icons::PAUSE)));
      }else {
        playButton->setIcon(QIcon(QString::fromStdString(Icons::PLAY)));
      }
    }
    void eventProcessor(Types::Event & event) {
      switch (event) {
      case Types::Event::SOUNDMAKER_PLAYLIST_SET:
        onPlaylistChanged();
        break;
      }
    }
  };

#endif // PLAYLISTLINEGIFUZE_H

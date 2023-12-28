/********************************************************************************
** Form generated from reading UI file 'playerWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QVariant>
#include <QApplication>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

#include "../ui.hpp"

class Player: public QWidget, StandartGlobalUser
{
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
    QLabel *label_2;
    QSlider *seekerSlider;
    QHBoxLayout *auxButtonLayout;
    QComboBox *loopComboBox;
    QPushButton *shuffleButton;
    QPushButton *addToFavouriteButton;
    QPushButton *addToPlaylistButton;
    QVBoxLayout *volumeLayout;
    QSlider *volumeSlider;
    QLabel *volumeLabel;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->setEnabled(true);
        Form->resize(400, 200);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Form->sizePolicy().hasHeightForWidth());
        Form->setSizePolicy(sizePolicy);
        Form->setMinimumSize(QSize(400, 200));
        Form->setMaximumSize(QSize(960, 200));
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        playerMainControlsLayout = new QVBoxLayout();
        playerMainControlsLayout->setObjectName(QString::fromUtf8("playerMainControlsLayout"));
        infoTrack = new QLabel(Form);
        infoTrack->setObjectName(QString::fromUtf8("infoTrack"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(infoTrack->sizePolicy().hasHeightForWidth());
        infoTrack->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(16);
        infoTrack->setFont(font);
        infoTrack->setWordWrap(true);
        infoTrack->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        playerMainControlsLayout->addWidget(infoTrack);

        artistInfoLayout = new QHBoxLayout();
        artistInfoLayout->setObjectName(QString::fromUtf8("artistInfoLayout"));
        infoArtist = new QLabel(Form);
        infoArtist->setObjectName(QString::fromUtf8("infoArtist"));
        QFont font1;
        font1.setPointSize(12);
        infoArtist->setFont(font1);
        infoArtist->setWordWrap(true);
        infoArtist->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        artistInfoLayout->addWidget(infoArtist);

        infoAlbum = new QLabel(Form);
        infoAlbum->setObjectName(QString::fromUtf8("infoAlbum"));
        infoAlbum->setFont(font1);
        infoAlbum->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        infoAlbum->setWordWrap(true);
        infoAlbum->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        artistInfoLayout->addWidget(infoAlbum);


        playerMainControlsLayout->addLayout(artistInfoLayout);

        infoFilename = new QLabel(Form);
        infoFilename->setObjectName(QString::fromUtf8("infoFilename"));
        sizePolicy1.setHeightForWidth(infoFilename->sizePolicy().hasHeightForWidth());
        infoFilename->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(7);
        infoFilename->setFont(font2);
        infoFilename->setWordWrap(true);
        infoFilename->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        playerMainControlsLayout->addWidget(infoFilename);

        playerMainButtons = new QHBoxLayout();
        playerMainButtons->setObjectName(QString::fromUtf8("playerMainButtons"));
        prevButton = new QPushButton(Form);
        prevButton->setObjectName(QString::fromUtf8("prevButton"));
        prevButton->setMinimumSize(QSize(0, 0));
        prevButton->setMaximumSize(QSize(50, 50));

        playerMainButtons->addWidget(prevButton);

        playButton = new QPushButton(Form);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setMinimumSize(QSize(0, 0));
        playButton->setMaximumSize(QSize(50, 50));
        playButton->setAutoFillBackground(false);

        playerMainButtons->addWidget(playButton);

        nextButton = new QPushButton(Form);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setMinimumSize(QSize(0, 0));
        nextButton->setMaximumSize(QSize(50, 50));

        playerMainButtons->addWidget(nextButton);


        playerMainControlsLayout->addLayout(playerMainButtons);

        seekerLayout = new QHBoxLayout();
        seekerLayout->setObjectName(QString::fromUtf8("seekerLayout"));
        label_2 = new QLabel(Form);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(16777215, 50));

        seekerLayout->addWidget(label_2);

        seekerSlider = new QSlider(Form);
        seekerSlider->setObjectName(QString::fromUtf8("seekerSlider"));
        seekerSlider->setMaximum(200);
        seekerSlider->setOrientation(Qt::Horizontal);
        seekerSlider->setTickPosition(QSlider::NoTicks);

        seekerLayout->addWidget(seekerSlider);


        playerMainControlsLayout->addLayout(seekerLayout);

        auxButtonLayout = new QHBoxLayout();
        auxButtonLayout->setObjectName(QString::fromUtf8("auxButtonLayout"));
        loopComboBox = new QComboBox(Form);
        loopComboBox->setObjectName(QString::fromUtf8("loopComboBox"));
        loopComboBox->setMaximumSize(QSize(100, 16777215));

        auxButtonLayout->addWidget(loopComboBox);

        shuffleButton = new QPushButton(Form);
        shuffleButton->setObjectName(QString::fromUtf8("shuffleButton"));
        shuffleButton->setMinimumSize(QSize(35, 35));
        shuffleButton->setMaximumSize(QSize(35, 35));

        auxButtonLayout->addWidget(shuffleButton);

        addToFavouriteButton = new QPushButton(Form);
        addToFavouriteButton->setObjectName(QString::fromUtf8("addToFavouriteButton"));
        addToFavouriteButton->setMinimumSize(QSize(35, 35));
        addToFavouriteButton->setMaximumSize(QSize(35, 35));

        auxButtonLayout->addWidget(addToFavouriteButton);

        addToPlaylistButton = new QPushButton(Form);
        addToPlaylistButton->setObjectName(QString::fromUtf8("addToPlaylistButton"));
        addToPlaylistButton->setMinimumSize(QSize(35, 35));
        addToPlaylistButton->setMaximumSize(QSize(35, 35));

        auxButtonLayout->addWidget(addToPlaylistButton);


        playerMainControlsLayout->addLayout(auxButtonLayout);


        horizontalLayout->addLayout(playerMainControlsLayout);

        volumeLayout = new QVBoxLayout();
        volumeLayout->setObjectName(QString::fromUtf8("volumeLayout"));
        volumeLayout->setSizeConstraint(QLayout::SetMinimumSize);
        volumeSlider = new QSlider(Form);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setMinimumSize(QSize(0, 0));
        volumeSlider->setMaximum(100);
        volumeSlider->setOrientation(Qt::Vertical);
        volumeSlider->setTickPosition(QSlider::TicksBelow);

        volumeLayout->addWidget(volumeSlider, 0, Qt::AlignRight);

        volumeLabel = new QLabel(Form);
        volumeLabel->setObjectName(QString::fromUtf8("volumeLabel"));

        volumeLayout->addWidget(volumeLabel, 0, Qt::AlignRight);


        horizontalLayout->addLayout(volumeLayout);

        // Icons setup
        prevButton->setIcon(QIcon(QString::fromStdString(Icons::PREV)));
        nextButton->setIcon(QIcon(QString::fromStdString(Icons::NEXT)));
        playButton->setIcon(QIcon(QString::fromStdString(Icons::PLAY)));

        addToPlaylistButton->setIcon(QIcon(QString::fromStdString(Icons::TOLIST)));
        addToFavouriteButton->setIcon(QIcon(QString::fromStdString(Icons::TOFAVOURITE)));
        shuffleButton->setIcon(QIcon(QString::fromStdString(Icons::SHUFFLE)));

        // Button actions connection
        connect(seekerSlider,&QSlider::sliderMoved,this,&Player::onSeekerMoved);
        connect(volumeSlider,&QSlider::sliderMoved,this,&Player::onVolumeMoved);
        connect(playButton,&QPushButton::pressed,this,&Player::onPlayPressed);
        connect(nextButton,&QPushButton::pressed,this,&Player::onNextPressed);
        connect(prevButton,&QPushButton::pressed,this,&Player::onPrevPressed);
        connect(shuffleButton,&QPushButton::pressed,this,&Player::onShufflePressed);
        connect(addToFavouriteButton,&QPushButton::pressed,this,&Player::onToFavouritePressed);
        connect(addToPlaylistButton,&QPushButton::pressed,this,&Player::onToPlaylistPressed);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        infoTrack->setText(QCoreApplication::translate("Form", "Track", nullptr));
        infoArtist->setText(QCoreApplication::translate("Form", "Artist", nullptr));
        infoAlbum->setText(QCoreApplication::translate("Form", "Album", nullptr));
        infoFilename->setText(QCoreApplication::translate("Form", "Filename", nullptr));
        prevButton->setText(QString());
        prevButton->setProperty("class", QVariant(QCoreApplication::translate("Form", "squareButtonMedium", nullptr)));
        playButton->setText(QString());
        playButton->setProperty("class", QVariant(QCoreApplication::translate("Form", "squareButtonMedium", nullptr)));
        nextButton->setText(QString());
        nextButton->setProperty("class", QVariant(QCoreApplication::translate("Form", "squareButtonMedium", nullptr)));
        label_2->setText(QCoreApplication::translate("Form", "04:20", nullptr));
        shuffleButton->setText(QString());
        shuffleButton->setProperty("class", QVariant(QCoreApplication::translate("Form", "squareButtonSmall", nullptr)));
        addToFavouriteButton->setText(QString());
        addToFavouriteButton->setProperty("class", QVariant(QCoreApplication::translate("Form", "squareButtonSmall", nullptr)));
        addToPlaylistButton->setText(QString());
        addToPlaylistButton->setProperty("class", QVariant(QCoreApplication::translate("Form", "squareButtonSmall", nullptr)));
        volumeLabel->setText(QCoreApplication::translate("Form", "100%", nullptr));
    } // retranslateUi

  Player(){
    Player::setupUi(this);
  }
  void onMediaPlayerMediaChange(){}
  void onMediaPlayerPositionChanged(){}
  void onMediaPlayerPlaying(){}
  void onPlayPressed(){}
  void onNextPressed(){}
  void onPrevPressed(){}
  void onSeekerMoved(){}
  void onVolumeMoved(){}
  void onNextTrackPressed(){}
  void onPrevTrackPressed(){}
  void onShufflePressed(){}
  void onToFavouritePressed(){}
  void onToPlaylistPressed(){}
};





#endif // PLAYERWIDGET_H

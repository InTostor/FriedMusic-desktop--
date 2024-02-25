/********************************************************************************
** Form generated from reading UI file 'Settings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QApplication>
#include <QCheckBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>

#include "../../StandartGlobalUser.hpp"
#include "../ui.hpp"

class Settings : public virtual StandartGlobalUser, public QWidget {
 public:
  QVBoxLayout *verticalLayout_5;
  QTabWidget *tabWidget;
  QWidget *accountConf;
  QFormLayout *formLayout_2;
  QLabel *label_10;
  QVBoxLayout *verticalLayout_2;
  QLineEdit *lineEdit_7;
  QLineEdit *lineEdit_8;
  QPushButton *pushButton;
  QWidget *behaviourTab;
  QGridLayout *gridLayout;
  QVBoxLayout *verticalLayout_4;
  QLabel *label_8;
  QHBoxLayout *horizontalLayout_8;
  QVBoxLayout *verticalLayout_3;
  QCheckBox *checkBox_4;
  QCheckBox *checkBox;
  QHBoxLayout *horizontalLayout_7;
  QLabel *label_7;
  QCheckBox *checkBox_2;
  QCheckBox *checkBox_3;
  QSpacerItem *verticalSpacer;
  QSpacerItem *horizontalSpacer;
  QWidget *pathsConf;
  QGridLayout *gridLayout_3;
  QHBoxLayout *horizontalLayout_10;
  QVBoxLayout *remotePathsLayout;
  QHBoxLayout *horizontalLayout_3;
  QLabel *label_3;
  QLineEdit *ApiUrlLineEdit;
  QHBoxLayout *horizontalLayout;
  QLabel *label_2;
  QLineEdit *RemoteMusicLineEdit;
  QHBoxLayout *horizontalLayout_2;
  QLabel *label;
  QLineEdit *RemoteUserdataLineEdit;
  QVBoxLayout *localPathsLayout;
  QHBoxLayout *horizontalLayout_6;
  QLabel *label_6;
  QLineEdit *DatabasePathLineEdit;
  QHBoxLayout *horizontalLayout_4;
  QLabel *label_5;
  QLineEdit *LocalMusicLineEdit;
  QHBoxLayout *horizontalLayout_5;
  QLabel *label_4;
  QLineEdit *LocalDataLineEdit;
  QLabel *label_9;
  QSpacerItem *verticalSpacer_2;
  QWidget *aboutPage;
  QVBoxLayout *verticalLayout;
  QLabel *aboutPageHeader;
  QLabel *aboutPageLabel_1;
  QLabel *aboutPageLabel_2;
  QLabel *aboutPageLabel_3;
  QLabel *aboutPageLabel_4;

  void setupUi() {
    QWidget *Settings = this;
    if (Settings->objectName().isEmpty())
      Settings->setObjectName(QString::fromUtf8("Settings"));
    Settings->resize(516, 335);
    verticalLayout_5 = new QVBoxLayout(Settings);
    verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
    tabWidget = new QTabWidget(Settings);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setTabPosition(QTabWidget::West);
    accountConf = new QWidget();
    accountConf->setObjectName(QString::fromUtf8("accountConf"));
    formLayout_2 = new QFormLayout(accountConf);
    formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
    label_10 = new QLabel(accountConf);
    label_10->setObjectName(QString::fromUtf8("label_10"));
    QFont font;
    font.setPointSize(36);
    label_10->setFont(font);

    formLayout_2->setWidget(0, QFormLayout::LabelRole, label_10);

    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout_2->setContentsMargins(0, 0, -1, -1);
    lineEdit_7 = new QLineEdit(accountConf);
    lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

    verticalLayout_2->addWidget(lineEdit_7);

    lineEdit_8 = new QLineEdit(accountConf);
    lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
    lineEdit_8->setEchoMode(QLineEdit::Password);

    verticalLayout_2->addWidget(lineEdit_8);

    pushButton = new QPushButton(accountConf);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    verticalLayout_2->addWidget(pushButton);

    formLayout_2->setLayout(1, QFormLayout::LabelRole, verticalLayout_2);

    tabWidget->addTab(accountConf, QString());
    behaviourTab = new QWidget();
    behaviourTab->setObjectName(QString::fromUtf8("behaviourTab"));
    gridLayout = new QGridLayout(behaviourTab);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    verticalLayout_4 = new QVBoxLayout();
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
    label_8 = new QLabel(behaviourTab);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setFont(font);

    verticalLayout_4->addWidget(label_8);

    horizontalLayout_8 = new QHBoxLayout();
    horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
    verticalLayout_3 = new QVBoxLayout();
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    checkBox_4 = new QCheckBox(behaviourTab);
    checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

    verticalLayout_3->addWidget(checkBox_4);

    checkBox = new QCheckBox(behaviourTab);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));

    verticalLayout_3->addWidget(checkBox);

    horizontalLayout_7 = new QHBoxLayout();
    horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
    label_7 = new QLabel(behaviourTab);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    horizontalLayout_7->addWidget(label_7);

    checkBox_2 = new QCheckBox(behaviourTab);
    checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

    horizontalLayout_7->addWidget(checkBox_2);

    checkBox_3 = new QCheckBox(behaviourTab);
    checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

    horizontalLayout_7->addWidget(checkBox_3);

    verticalLayout_3->addLayout(horizontalLayout_7);

    verticalSpacer =
        new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_3->addItem(verticalSpacer);

    horizontalLayout_8->addLayout(verticalLayout_3);

    horizontalSpacer =
        new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_8->addItem(horizontalSpacer);

    verticalLayout_4->addLayout(horizontalLayout_8);

    gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);

    tabWidget->addTab(behaviourTab, QString());
    pathsConf = new QWidget();
    pathsConf->setObjectName(QString::fromUtf8("pathsConf"));
    gridLayout_3 = new QGridLayout(pathsConf);
    gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
    horizontalLayout_10 = new QHBoxLayout();
    horizontalLayout_10->setObjectName(
        QString::fromUtf8("horizontalLayout_10"));
    remotePathsLayout = new QVBoxLayout();
    remotePathsLayout->setObjectName(QString::fromUtf8("remotePathsLayout"));
    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    label_3 = new QLabel(pathsConf);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    horizontalLayout_3->addWidget(label_3);

    ApiUrlLineEdit = new QLineEdit(pathsConf);
    ApiUrlLineEdit->setObjectName(QString::fromUtf8("ApiUrlLineEdit"));

    horizontalLayout_3->addWidget(ApiUrlLineEdit);

    remotePathsLayout->addLayout(horizontalLayout_3);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label_2 = new QLabel(pathsConf);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout->addWidget(label_2);

    RemoteMusicLineEdit = new QLineEdit(pathsConf);
    RemoteMusicLineEdit->setObjectName(
        QString::fromUtf8("RemoteMusicLineEdit"));

    horizontalLayout->addWidget(RemoteMusicLineEdit);

    remotePathsLayout->addLayout(horizontalLayout);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    label = new QLabel(pathsConf);
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout_2->addWidget(label);

    RemoteUserdataLineEdit = new QLineEdit(pathsConf);
    RemoteUserdataLineEdit->setObjectName(
        QString::fromUtf8("RemoteUserdataLineEdit"));

    horizontalLayout_2->addWidget(RemoteUserdataLineEdit);

    remotePathsLayout->addLayout(horizontalLayout_2);

    horizontalLayout_10->addLayout(remotePathsLayout);

    localPathsLayout = new QVBoxLayout();
    localPathsLayout->setObjectName(QString::fromUtf8("localPathsLayout"));
    horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
    label_6 = new QLabel(pathsConf);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    horizontalLayout_6->addWidget(label_6);

    DatabasePathLineEdit = new QLineEdit(pathsConf);
    DatabasePathLineEdit->setObjectName(
        QString::fromUtf8("DatabasePathLineEdit"));

    horizontalLayout_6->addWidget(DatabasePathLineEdit);

    localPathsLayout->addLayout(horizontalLayout_6);

    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    label_5 = new QLabel(pathsConf);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    horizontalLayout_4->addWidget(label_5);

    LocalMusicLineEdit = new QLineEdit(pathsConf);
    LocalMusicLineEdit->setObjectName(QString::fromUtf8("LocalMusicLineEdit"));

    horizontalLayout_4->addWidget(LocalMusicLineEdit);

    localPathsLayout->addLayout(horizontalLayout_4);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    label_4 = new QLabel(pathsConf);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    horizontalLayout_5->addWidget(label_4);

    LocalDataLineEdit = new QLineEdit(pathsConf);
    LocalDataLineEdit->setObjectName(QString::fromUtf8("LocalDataLineEdit"));

    horizontalLayout_5->addWidget(LocalDataLineEdit);

    localPathsLayout->addLayout(horizontalLayout_5);

    horizontalLayout_10->addLayout(localPathsLayout);

    gridLayout_3->addLayout(horizontalLayout_10, 1, 0, 1, 1);

    label_9 = new QLabel(pathsConf);
    label_9->setObjectName(QString::fromUtf8("label_9"));
    label_9->setFont(font);

    gridLayout_3->addWidget(label_9, 0, 0, 1, 1);

    verticalSpacer_2 =
        new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_3->addItem(verticalSpacer_2, 2, 0, 1, 1);

    tabWidget->addTab(pathsConf, QString());
    aboutPage = new QWidget();
    aboutPage->setObjectName(QString::fromUtf8("aboutPage"));
    verticalLayout = new QVBoxLayout(aboutPage);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    aboutPageHeader = new QLabel(aboutPage);
    aboutPageHeader->setObjectName(QString::fromUtf8("aboutPageHeader"));
    aboutPageHeader->setMaximumSize(QSize(16777215, 70));
    aboutPageHeader->setFont(font);

    verticalLayout->addWidget(aboutPageHeader);

    aboutPageLabel_1 = new QLabel(aboutPage);
    aboutPageLabel_1->setObjectName(QString::fromUtf8("aboutPageLabel_1"));
    aboutPageLabel_1->setMaximumSize(QSize(16777215, 60));
    QFont font1;
    font1.setPointSize(24);
    aboutPageLabel_1->setFont(font1);

    verticalLayout->addWidget(aboutPageLabel_1);

    aboutPageLabel_2 = new QLabel(aboutPage);
    aboutPageLabel_2->setObjectName(QString::fromUtf8("aboutPageLabel_2"));
    aboutPageLabel_2->setMaximumSize(QSize(16777215, 50));
    aboutPageLabel_2->setAlignment(Qt::AlignLeading | Qt::AlignLeft |
                                   Qt::AlignTop);

    verticalLayout->addWidget(aboutPageLabel_2);

    aboutPageLabel_3 = new QLabel(aboutPage);
    aboutPageLabel_3->setObjectName(QString::fromUtf8("aboutPageLabel_3"));

    verticalLayout->addWidget(aboutPageLabel_3);

    aboutPageLabel_4 = new QLabel(aboutPage);
    aboutPageLabel_4->setObjectName(QString::fromUtf8("aboutPageLabel_4"));
    aboutPageLabel_4->setAlignment(Qt::AlignBottom | Qt::AlignLeading |
                                   Qt::AlignLeft);

    verticalLayout->addWidget(aboutPageLabel_4);

    tabWidget->addTab(aboutPage, QString());

    verticalLayout_5->addWidget(tabWidget);

    retranslateUi(Settings);

    tabWidget->setCurrentIndex(2);

    QMetaObject::connectSlotsByName(Settings);
    // get current config
    ApiUrlLineEdit->setText(QString::fromStdString(getConfigValue("apiUrl")));
    RemoteMusicLineEdit->setText(QString::fromStdString(getConfigValue("musicStorageUrl")));
    RemoteUserdataLineEdit->setText(QString::fromStdString(getConfigValue("userdataStorageUrl")));
    DatabasePathLineEdit->setText(QString::fromStdString(getConfigValue("databasePath")));
    LocalMusicLineEdit->setText(QString::fromStdString(getConfigValue("localMusicStoragePath")));
    LocalDataLineEdit->setText(QString::fromStdString(getConfigValue("localUserdataStoragePath")));

  }  // setupUi

  void retranslateUi(QWidget *Settings) {
    Settings->setWindowTitle(
        QCoreApplication::translate("Settings", "Form", nullptr));
    label_10->setText(
        QCoreApplication::translate("Settings", "Account", nullptr));
    lineEdit_7->setInputMask(QString());
    lineEdit_7->setPlaceholderText(
        QCoreApplication::translate("Settings", "Login", nullptr));
    lineEdit_8->setText(QString());
    lineEdit_8->setPlaceholderText(
        QCoreApplication::translate("Settings", "Password", nullptr));
    pushButton->setText(
        QCoreApplication::translate("Settings", "Login", nullptr));
    tabWidget->setTabText(
        tabWidget->indexOf(accountConf),
        QCoreApplication::translate("Settings", "Account", nullptr));
    label_8->setText(
        QCoreApplication::translate("Settings", "App behaviour", nullptr));
    checkBox_4->setText(QCoreApplication::translate(
        "Settings", "Authenticate on server on start", nullptr));
    checkBox->setText(QCoreApplication::translate(
        "Settings", "Pull remote on start", nullptr));
    label_7->setText(
        QCoreApplication::translate("Settings", "Push remote", nullptr));
    checkBox_2->setText(
        QCoreApplication::translate("Settings", "on close", nullptr));
    checkBox_3->setText(
        QCoreApplication::translate("Settings", "on any update", nullptr));
    tabWidget->setTabText(
        tabWidget->indexOf(behaviourTab),
        QCoreApplication::translate("Settings", "Behaviour", nullptr));
    label_3->setText(
        QCoreApplication::translate("Settings", "API URl", nullptr));
    label_2->setText(QCoreApplication::translate(
        "Settings", "Remote music storage (http, ftp, rtp etc)", nullptr));
    label->setText(QCoreApplication::translate(
        "Settings", "Remote userdata storage (http,ftp,rtp etc)", nullptr));
    label_6->setText(QCoreApplication::translate(
        "Settings", "Local database path", nullptr));
    label_5->setText(QCoreApplication::translate(
        "Settings", "Local music storage", nullptr));
    label_4->setText(QCoreApplication::translate(
        "Settings", "Local userdata storage", nullptr));
    label_9->setText(QCoreApplication::translate("Settings", "Paths", nullptr));
    tabWidget->setTabText(
        tabWidget->indexOf(pathsConf),
        QCoreApplication::translate("Settings", "Paths", nullptr));
    aboutPageHeader->setText(
        QCoreApplication::translate("Settings", "About", nullptr));
    aboutPageLabel_1->setText(
        QCoreApplication::translate("Settings", "Fried Music", nullptr));
    aboutPageLabel_2->setText(
        QCoreApplication::translate("Settings", "Qt 5 multiplatform", nullptr));
    aboutPageLabel_3->setText(QCoreApplication::translate(
        "Settings", "Music player with remote/self hosted library", nullptr));
    aboutPageLabel_4->setText(QCoreApplication::translate(
        "Settings", "InTostor. MIT license", nullptr));
    tabWidget->setTabText(
        tabWidget->indexOf(aboutPage),
        QCoreApplication::translate("Settings", "About", nullptr));
  }  // retranslateUi

  Settings() {}
  ~Settings() {}
};

#endif  // SETTINGS_H

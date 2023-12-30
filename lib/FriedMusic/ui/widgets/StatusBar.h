/********************************************************************************
** Form generated from reading UI file 'statusBar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVariant>
#include <QWidget>

#include "../../macro.hpp"
#include "../ui.hpp"
#include "Settings.h"

class StatusBar : public QWidget, public virtual StandartGlobalUser {
 public:
  QHBoxLayout *horizontalLayout;
  QLabel *loggedAsLabel;
  QPushButton *settingsButton;
  Settings *settingsMenu;

  void setupUi(QWidget *StatusBar) {
    if (StatusBar->objectName().isEmpty())
      StatusBar->setObjectName(QString::fromUtf8("StatusBar"));
    StatusBar->resize(160, 53);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(StatusBar->sizePolicy().hasHeightForWidth());
    StatusBar->setSizePolicy(sizePolicy);
    StatusBar->setMaximumSize(QSize(16777215, 53));
    horizontalLayout = new QHBoxLayout(StatusBar);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    loggedAsLabel = new QLabel(StatusBar);
    loggedAsLabel->setObjectName(QString::fromUtf8("loggedAsLabel"));
    sizePolicy.setHeightForWidth(
        loggedAsLabel->sizePolicy().hasHeightForWidth());
    loggedAsLabel->setSizePolicy(sizePolicy);
    loggedAsLabel->setMaximumSize(QSize(16777215, 50));

    horizontalLayout->addWidget(loggedAsLabel);

    settingsButton = new QPushButton(StatusBar);
    settingsButton->setObjectName(QString::fromUtf8("settingsButton"));
    settingsButton->setMinimumSize(QSize(35, 35));
    settingsButton->setMaximumSize(QSize(35, 35));
    settingsButton->setIcon(QIcon(QString::fromStdString(Icons::SETTINGS)));

    horizontalLayout->addWidget(settingsButton);
    connect(settingsButton, &QPushButton::pressed, this,
            &StatusBar::onSettingsOpen);

    retranslateUi(StatusBar);

    QMetaObject::connectSlotsByName(StatusBar);
  }  // setupUi

  void retranslateUi(QWidget *StatusBar) {
    StatusBar->setWindowTitle(
        QCoreApplication::translate("StatusBar", "Form", nullptr));
    loggedAsLabel->setText(QCoreApplication::translate(
        "StatusBar", "logged as InTostor", nullptr));
    settingsButton->setText(QString());
  }  // retranslateUi
  StatusBar() { StatusBar::setupUi(this); }

  void onSettingsOpen() {
    settingsMenu = new Settings();
    settingsMenu->setGlobals(this->soundmaker, this->client);
    settingsMenu->show();
  }
};

#endif  // STATUSBAR_H

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
#include <iostream>
#include <string>

using namespace std;

#include "../../StandartGlobalUser.hpp"
#include "../../macro.hpp"
#include "../ui.hpp"
#include "Settings.h"

class StatusBar : public virtual StandartGlobalUser, public QWidget {
 public:
  QHBoxLayout *horizontalLayout;
  QLabel *loggedAsLabel;
  QPushButton *settingsButton;
  Settings *settingsMenu = NULL;

  void setupUi() {
    if (this->QWidget::objectName().isEmpty())
      this->QWidget::setObjectName(QString::fromUtf8("StatusBar"));
    this->resize(160, 53);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setMaximumSize(QSize(16777215, 53));
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    loggedAsLabel = new QLabel(this);
    loggedAsLabel->setObjectName(QString::fromUtf8("loggedAsLabel"));
    sizePolicy.setHeightForWidth(
        loggedAsLabel->sizePolicy().hasHeightForWidth());
    loggedAsLabel->setSizePolicy(sizePolicy);
    loggedAsLabel->setMaximumSize(QSize(16777215, 50));

    horizontalLayout->addWidget(loggedAsLabel);

    settingsButton = new QPushButton(this);
    settingsButton->setObjectName(QString::fromUtf8("settingsButton"));
    settingsButton->setMinimumSize(QSize(35, 35));
    settingsButton->setMaximumSize(QSize(35, 35));
    settingsButton->setIcon(QIcon(QString::fromStdString(Icons::SETTINGS)));

    horizontalLayout->addWidget(settingsButton);
    this->QWidget::connect(settingsButton, &QPushButton::pressed, this,
                           &StatusBar::onSettingsOpen);

    retranslateUi();

    // QMetaObject::connectSlotsByName(this);
    QMetaObject::connectSlotsByName(static_cast<QWidget *>(this));
  }  // setupUi

  void retranslateUi() {
    this->setWindowTitle(
        QCoreApplication::translate("StatusBar", "Form", nullptr));
    loggedAsLabel->setText(QCoreApplication::translate(
        "StatusBar", "placeholder: logged as <username>", nullptr));
    settingsButton->setText(QString());
  }  // retranslateUi
  StatusBar() {}

  void onSettingsOpen() {
    settingsMenu = new Settings();
    settingsMenu->setGlobals(this->soundmaker, this->client);
    settingsMenu->setupUi();
    settingsMenu->show();
  }
  void onAuthenticationTryed() {
    if (!client->isServerAccessible()) {
      loggedAsLabel->setText(
          QString::fromUtf8("Offline, server is not accessible"));
      return;
    }
    string username = client->getUsername();
    if (username == "anonymous" & client->isServerAccessible()) {
      loggedAsLabel->setText(QString::fromUtf8(
          "Logged as anonymous, but network available. Check credentials"));
    } else {
      loggedAsLabel->setText(QString::fromStdString("Logged as " + username));
    }
  }
  void eventProcessor(const Types::Event &event){
    switch (event)
    {
    case Types::Event::AUTHENTICATION_TRYED:
      onAuthenticationTryed();
      break;
    
    default:
      break;
    }
  }
};

#endif  // STATUSBAR_H

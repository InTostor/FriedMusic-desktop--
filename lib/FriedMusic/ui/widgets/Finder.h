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
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QScrollArea>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>

#include "../../StandartGlobalUser.hpp"
#include "../ui.hpp"

class Finder : public virtual StandartGlobalUser, public QWidget{
 public:
  QGridLayout *gridLayout;
  QTabWidget *tab;
  QWidget *searchTab;
  QVBoxLayout *verticalLayout_2;
  QLineEdit *searchLine;
  QListWidget *searchResult;
  QWidget *filesTab;
  QGridLayout *gridLayout_2;
  QScrollArea *playlistScroll;
  QWidget *playlistScrollContent;
  QHBoxLayout *horizontalLayout_3;

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
    searchLine = new QLineEdit(searchTab);
    searchLine->setObjectName(QString::fromUtf8("searchLine"));

    verticalLayout_2->addWidget(searchLine);

    searchResult = new QListWidget(searchTab);
    searchResult->setObjectName(QString::fromUtf8("searchResult"));

    verticalLayout_2->addWidget(searchResult);

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

    QMetaObject::connectSlotsByName(this);
  }  // setupUi

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
  }  // retranslateUi
  Finder() {}
};

#endif  // FINDER_H

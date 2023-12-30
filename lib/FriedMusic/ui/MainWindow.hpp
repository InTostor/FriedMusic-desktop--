#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <Qt>

#include "ui.hpp"
#include "widgets/Player.h"
#include "widgets/Finder.h"
#include "widgets/StatusBar.h"


class MainWindow: public QWidget, public virtual StandartGlobalUser{
public:
Player *playerWidget;
Finder *finderWidget;
StatusBar *statusBarWidget;
QSplitter *horizontalSplitter;
// finder, status bar, other
void setupUi(QWidget *Form){
  playerWidget = new Player();
  playerWidget->setGlobals(this->soundmaker,this->client);
  finderWidget = new Finder();
  finderWidget->setGlobals(this->soundmaker,this->client);
  statusBarWidget = new StatusBar();
  statusBarWidget->setGlobals(this->soundmaker,this->client);

  horizontalSplitter = new QSplitter(Qt::Horizontal,nullptr);
  horizontalSplitter->setMaximumSize(9999,9999);
  horizontalSplitter->addWidget(playerWidget);
  horizontalSplitter->addWidget(finderWidget);
  horizontalSplitter->setStretchFactor(1,1);

  this->setWindowTitle("Fried Music");
  QVBoxLayout *layout;
  layout = new QVBoxLayout(this);
  
  layout->addWidget(statusBarWidget);
  layout->addWidget(horizontalSplitter);

  
}
MainWindow(){
  MainWindow::setupUi(this);
}

};

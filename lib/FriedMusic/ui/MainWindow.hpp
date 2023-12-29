#pragma once
#include <QWidget>
#include <QVBoxLayout>

#include "ui.hpp"
#include "widgets/Player.h"


class MainWindow: public QWidget, public virtual StandartGlobalUser{
public:
Player *playerWidget;
// finder, status bar, other
void setupUi(QWidget *Form){
  playerWidget = new Player();
  playerWidget->setGlobals(this->soundmaker,this->client);
  this->setLayout(new QVBoxLayout(this));
  this->layout()->addWidget(playerWidget);
  
}
MainWindow(){
  MainWindow::setupUi(this);
}

};

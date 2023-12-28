#include <iostream>
#include <vector>
#include <string>
#include "FriedMusic/Data.hpp"
#include "FriedMusic/macro.hpp"
#include <cpr/cpr.h>

#include <QApplication>

#include "FriedMusic/ui/widgets/Player.h"



using namespace std;

int main(int argc, char *argv[]){

  QApplication app(argc,argv);

  Player playerWidget;
  playerWidget.show();

  return app.exec();
}
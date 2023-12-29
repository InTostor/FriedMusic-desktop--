#include <iostream>
#include <vector>
#include <string>



#include "FriedMusic/Data.hpp"
#include "FriedMusic/Client.hpp"
#include "FriedMusic/macro.hpp"
#include "FriedMusic/SoundMaker.hpp"
#include <cpr/cpr.h>

#include <QApplication>

#include "FriedMusic/ui/MainWindow.hpp"

using namespace std;




int main(int argc, char *argv[]){
  
  Client* client;
  SoundMaker* soundmaker;
  
  

  QApplication app(argc,argv);
  MainWindow mainWindow;

  mainWindow.setGlobals(soundmaker,client);
  mainWindow.show();
  return app.exec();
}
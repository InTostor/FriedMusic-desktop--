#include <cpr/cpr.h>

#include "globals.h"

#include <QApplication>
#include <QFile>
#include <iostream>
#include <string>
#include <vector>

#include "Client.hpp"
#include "Data.hpp"
#include "SoundMaker.hpp"
#include "macro.hpp"
#include "ui/MainWindow.hpp"


using namespace std;


int main(int argc, char *argv[]) {

  
  QApplication app(argc, argv);

  app.setWindowIcon(QIcon("resource/logo.ico"));
  try {
    QFile styleFile("resource/style.qss");
    styleFile.open(QFile::ReadOnly);
    QString style(styleFile.readAll());
    app.setStyleSheet(style);
  } catch (...) {
  }
  MainWindow *mainWindow = new MainWindow();
  soundmaker.make();

  mainWindow->setupUi();
  client.authenticate("InTostor", "Cummunism");
  // client.downloadDatabase();

  mainWindow->show();

  return app.exec();
}
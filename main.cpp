#include <cpr/cpr.h>

#include <QApplication>
#include <QFile>
#include <iostream>
#include <string>
#include <vector>

#include "lib/FriedMusic/Client.hpp"
#include "lib/FriedMusic/Data.hpp"
#include "lib/FriedMusic/SoundMaker.hpp"
#include "lib/FriedMusic/macro.hpp"
#include "lib/FriedMusic/ui/MainWindow.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  Client* client;
  SoundMaker* soundmaker;

  client = new Client();
  QApplication app(argc, argv);

  app.setWindowIcon(QIcon("resource/logo.ico"));
  try {
    QFile styleFile("resource/style.qss");
    styleFile.open(QFile::ReadOnly);
    QString style(styleFile.readAll());
    app.setStyleSheet(style);
  } catch (...) {
  }
  MainWindow* mainWindow = new MainWindow();
  soundmaker = mainWindow->soundmaker;

  mainWindow->client = client;
  mainWindow->setupUi();
  client->authenticate("InTostor", "Cummunism");
  // client->downloadDatabase();

  Source plSource("./userdata/history.fpl", Types::StorageType::LOCAL,
                  Types::PathType::FILESYSTEMPATH, Types::DataType::PLAYLIST);
  Playlist pl = client->getPlaylistFromSource(plSource, true);

  soundmaker->setPlaylist(pl);
  
  mainWindow->show();

  return app.exec();
}
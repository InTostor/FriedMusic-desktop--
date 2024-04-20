#include <cpr/cpr.h>

#include "globals.h"

#include <QApplication>
#include <QFile>
#include <cstddef>
#include <iostream>
#include <qerrormessage.h>
#include <qmessagebox.h>
#include <string>
#include <vector>

#include "Client.hpp"
#include "Data.hpp"
#include "SoundMaker.hpp"
#include "macro.hpp"
#include "ui/MainWindow.hpp"
#include <QErrorMessage>
#include <QMessageBox>

using namespace std;

int main(int argc, char *argv[]) {
  // init

  QApplication app(argc, argv);

  if (!filesystem::exists("config.json")) {
    
    QMessageBox::critical(
      nullptr,
      QString::fromUtf8(
        "Critical error"),
        QString::fromUtf8("No config file found. \n get config from source or rebuild app."));
    return app.exec();
  }
  if (!filesystem::exists(Config::Config::getConfigValue("databasePath"))) {
    // QErrorMessage *errorMessage = new QErrorMessage();
    switch (QMessageBox::question(
        nullptr, QString::fromUtf8("Bad database"),
        QString::fromUtf8("Database is not valid, or does not exist. Would you "
                          "like to download database?\n(Can take a while to load, just wait)"),
        QMessageBox::Yes | QMessageBox::No)) {
    case QMessageBox::Yes:
      client.downloadDatabase();
      break;
    }

  }
  if (Config::Config::getConfigBoolValue("authenticateOnStart")) {
    client.authenticate(Config::Config::getConfigValue("username"), Config::Config::getConfigValue("password"));
  }
  // cout <<
  // filesystem::last_write_time(filesystem::path(Config::Config::getConfigValue("databasePath")))
  // << endl;

  app.setWindowIcon(QIcon("resource/logo.ico"));
  try {
    QFile styleFile("resource/style.qss");
    styleFile.open(QFile::ReadOnly);
    QString style(styleFile.readAll());
    app.setStyleSheet(style);
  } catch (...) {
  }
  MainWindow *mainWindow = new MainWindow();
  soundmaker->make();

  mainWindow->setupUi();

  // client.downloadDatabase();
  mainWindow->show();

  return app.exec();
}
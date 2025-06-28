// Copyright 2022 Flying-Tom

#include <game.h>
#include <mainwindow.h>

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  MainWindow w;
  w.setWindowIcon(QIcon(":/images/icon.png"));
  w.setWindowTitle("Tom's TD Game");
  w.show();

  return a.exec();
}

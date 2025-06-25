// Copyright 2022 Flying-Tom

#include <mainwindow.h>

#include <QPushButton>
#include <iostream>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  setFixedSize(1600, 960);
  QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
  move((screenGeometry.width() - width()) / 2,
       (screenGeometry.height() - height()) / 2 - 50);
  starticonangle = 0;
  game = nullptr;
  mapConfig = QString(":maps/map1.txt");
  setCursor(QCursor(QPixmap(":images/mouse.png")));

  QWidget* menu = new QWidget(this);

  setCentralWidget(menu);

  QString menuButtonStyle(
      "QPushButton{border-image: "
      "url(:/images/startbutton.png);color:rgb(255,255,255);font:bold "
      "20px;}"
      "QPushButton:hover{border-image: "
      "url(:/images/lightstartbutton.png);color:rgb(255,255,255);font:bold "
      "26px;}");

  QPushButton* startGameButton = new QPushButton("Start Game");

  startGameButton->setParent(menu);
  startGameButton->move(700, 460);
  startGameButton->resize(200, 100);
  startGameButton->setStyleSheet(menuButtonStyle);

  connect(startGameButton, &QPushButton::clicked, this, &MainWindow::startGame);

  QPushButton* chooseMapButton = new QPushButton("Choose Map");
  chooseMapButton->setParent(menu);
  chooseMapButton->move(700, 580);
  chooseMapButton->resize(200, 100);
  chooseMapButton->setStyleSheet(menuButtonStyle);

  QPushButton* exportMapButton = new QPushButton("Export Map");
  exportMapButton->setParent(menu);
  exportMapButton->move(700, 700);
  exportMapButton->resize(200, 100);
  exportMapButton->setStyleSheet(menuButtonStyle);

  QPushButton* ExitButton = new QPushButton("Exit Game");
  ExitButton->setParent(menu);
  ExitButton->move(700, 820);
  ExitButton->resize(200, 100);
  ExitButton->setStyleSheet(menuButtonStyle);

  connect(chooseMapButton, &QPushButton::clicked, this, &MainWindow::chooseMap);
  connect(exportMapButton, &QPushButton::clicked, this, &MainWindow::exportMap);
  connect(ExitButton, &QPushButton::clicked, this, &MainWindow::close);

  menu->show();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Escape:
      if (game) {
        delete game;
        game = nullptr;
      }
      break;
    case Qt::Key_S:
      startGame();
      break;
    default:
      event->ignore();
      break;
  }
}

void MainWindow::paintEvent(QPaintEvent* e) {
  Q_UNUSED(e)
  QPainter p(this);
  p.setOpacity(1);
  p.drawImage(rect(), QImage(":/images/startupbackground1.png"));
  p.setOpacity(0.6);
  p.drawImage(rect(), QImage(":/images/startupbackground2.png"));
  p.setOpacity(1);
  p.drawImage(QRectF(604, 200, 391, 180), QImage(":/images/gametitle.png"));
  p.drawImage(QRectF(768, 120, 64, 64), QImage(":/images/icon.png"));
}

Game* MainWindow::getGame() const { return game; }

void MainWindow::setGame(Game* newGame) { game = newGame; }

void MainWindow::startGame() {
  game = new Game(this, &mapConfig);
  game->show();
}

void MainWindow::chooseMap() {
  QString path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                              "../TDGame/resource/maps",
                                              tr("Text File (*.txt)"));
  if (path.isEmpty()) {
    return;
  }
  mapConfig = QString(path);
}

void MainWindow::exportMap() {
  QString path = QFileDialog::getSaveFileName(this, tr("Open File"), ".",
                                              tr("Text File (*.txt)"));
  if (path.isEmpty()) {
    return;
  }
  QFile::copy(mapConfig, path);
  QFile exportConfig(path);
  exportConfig.setPermissions(QFile::WriteUser | QFile::ReadUser);
}

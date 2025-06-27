// Copyright 2022 Flying-Tom

#include <mainwindow.h>

#include <QPushButton>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  setFixedSize(1440, 960);
  // QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
  QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
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

  int buttonStartX = 650, buttonStartY = 430;
  int buttonWidth = 200, buttonHeight = 100;
  int buttonInterval = 120;

  QPushButton* startGameButton = new QPushButton("Start Game");
  connect(startGameButton, &QPushButton::clicked, this, &MainWindow::startGame);
  startGameButton->setParent(menu);
  startGameButton->move(buttonStartX, buttonStartY);
  startGameButton->resize(buttonWidth, buttonHeight);
  startGameButton->setStyleSheet(menuButtonStyle);

  QPushButton* chooseMapButton = new QPushButton("Choose Map");
  connect(chooseMapButton, &QPushButton::clicked, this, &MainWindow::chooseMap);
  chooseMapButton->setParent(menu);
  chooseMapButton->move(buttonStartX, buttonStartY + buttonInterval);
  chooseMapButton->resize(buttonWidth, buttonHeight);
  chooseMapButton->setStyleSheet(menuButtonStyle);

  QPushButton* exportMapButton = new QPushButton("Export Map");
  connect(exportMapButton, &QPushButton::clicked, this, &MainWindow::exportMap);
  exportMapButton->setParent(menu);
  exportMapButton->move(buttonStartX, buttonStartY + buttonInterval * 2);
  exportMapButton->resize(buttonWidth, buttonHeight);
  exportMapButton->setStyleSheet(menuButtonStyle);

  QPushButton* ExitButton = new QPushButton("Exit Game");
  connect(ExitButton, &QPushButton::clicked, this, &MainWindow::close);
  ExitButton->setParent(menu);
  ExitButton->move(buttonStartX, buttonStartY + buttonInterval * 3);
  ExitButton->resize(buttonWidth, buttonHeight);
  ExitButton->setStyleSheet(menuButtonStyle);

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
  p.drawImage(QRectF(720, 120, 64, 64), QImage(":/images/icon.png"));
  p.drawImage(QRectF(560, 200, 391, 180), QImage(":/images/gametitle.png"));
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

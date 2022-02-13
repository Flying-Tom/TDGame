// Copyright 2022 Flying-Tom
#ifndef INCLUDE_MAINWINDOW_H_
#define INCLUDE_MAINWINDOW_H_

#include <common.h>
#include <game.h>

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  void keyPressEvent(QKeyEvent* event) override;
  void paintEvent(QPaintEvent* e) override;

  Game* getGame() const;
  void setGame(Game* newGame);
  QString mapConfig;

  //    void loadStyleSheet(const QString &styleSheetFile);

 public slots:
  void startGame();
  void chooseMap();
  void exportMap();

 private:
  Game* game;
  int starticonangle;
};

#endif  // INCLUDE_MAINWINDOW_H_

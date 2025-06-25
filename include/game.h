// Copyright 2022 Flying-Tom
#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <common.h>
#include <gamemap.h>
#include <statistic.h>
// #include <mainwindow.h>

#include <vector>

class Game : public QGraphicsView {
  Q_OBJECT

 public:
  explicit Game(QMainWindow* parent, QString* mapConfig = 0);
  ~Game();

 public:
  QMainWindow* parent;
  QGraphicsScene scene;
  GameMap map;
  Statistic statistic;
  QString* mapConfig;

  int enemyNum;
  int enemyMaxnum;

  void createEnemy(int num, int interval);
  void updateGameSpeed();
  void keyPressEvent(QKeyEvent* event) override;
 signals:
  void GameOver();
 public slots:
  void spawnEnemy();
  void endThisGame(QString);

 public:
  int gameSpeed;
  QTimer spawnTimer;
  QTimer advanceTimer;
  QElapsedTimer FPSCounterTimer;

  QMediaPlayer BGMplayer;

  std::vector<int> probEnemy;
  std::vector<int> probRec;
  std::vector<std::function<void(Enemy*&)>> enemyLambda;
  int probSum;
  int RandEnemyIndex();
};

#endif  // INCLUDE_GAME_H_

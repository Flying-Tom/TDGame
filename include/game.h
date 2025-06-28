// Copyright 2022 Flying-Tom
#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <common.h>
#include <gamemap.h>
#include <shop.h>
#include <statistic.h>

class Game : public QGraphicsView {
  Q_OBJECT

  int gameSpeed = 50;
  int spawnSpeed = 50;
  int probSum;

  QTimer spawnTimer;
  QTimer advanceTimer;
  QMediaPlayer BGMplayer;

  QVector<int> probEnemy;
  QVector<int> probRec;
  QVector<std::function<void(Enemy *&)>> enemyLambda;

public:
  explicit Game(QMainWindow *parent, QString *mapConfig = 0);
  ~Game();

public:
  QMainWindow *parent;
  QGraphicsScene scene;
  GameMap *map;
  Statistic *statistic;
  Shop shop;
  QString *mapConfig;
  QElapsedTimer FPSCounterTimer;

  int randEnemyIndex();
  bool isPaused() const;
  void enemyWave(int num);
  void updateGameSpeed();
  void keyPressEvent(QKeyEvent *event) override;

signals:
  void GameOver();
public slots:
  void spawnEnemy();
  void startSpawn(bool force = false);
  void stopSpawn();
  void endThisGame(QString);
  // int RandEnemyIndex();
};

#endif // INCLUDE_GAME_H_

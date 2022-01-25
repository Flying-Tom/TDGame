#ifndef GAME_H
#define GAME_H

#include <common.h>
#include <mainwindow.h>
#include <map.h>
#include <statistic.h>

class Game : public QGraphicsView {
    Q_OBJECT
public:
    Game(MainWindow* parent = 0, QString mapConfig = QString(":maps/map1.txt"));
    ~Game();

public:
    MainWindow* parent;
    QGraphicsScene scene;
    Map map;
    Statistic statistic;
    QString mapConfig;

    int enemyNum;
    int enemyMaxnum;

    void createEnemy(int num);
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

#endif // GAME_H

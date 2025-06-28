// Copyright 2022 Flying-Tom

#include <enemy/blackwarrior.h>
#include <enemy/cowardplane.h>
#include <enemy/dragon.h>
#include <enemy/fallenwarrior.h>
#include <enemy/ghost.h>
#include <enemy/robotsoldier.h>
#include <enemy/shaman.h>
#include <enemy/spirit.h>
#include <game.h>

Game::Game(QMainWindow *parent, QString *mapConfig)
    : QGraphicsView(parent),
      // parent(parent),
      scene(this), shop(this), mapConfig(mapConfig), BGMplayer(this) {
  /* main UI of the game init */
  scene.setSceneRect(0, 0, GameMap::width + 320, GameMap::height);
  setFixedSize(GameMap::width + 320, GameMap::height);

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setRenderHint(QPainter::Antialiasing);
  setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  setScene(&scene);

  map = new GameMap(this, mapConfig);
  scene.addItem(map);
  scene.setBackgroundBrush(QPixmap::fromImage(map->mapImage));

  statistic = new Statistic(this);
  scene.addItem(statistic);

  FPSCounterTimer.start();

  connect(&advanceTimer, SIGNAL(timeout()), &scene, SLOT(advance()));
  connect(&spawnTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));

  updateGameSpeed();

  /* media init */
  // BGMplayer->setMedia(QUrl("xxx/PartyTime.mp3"));
  BGMplayer.play();

  /* enemy spawning system based on probability init */
  probEnemy = {100, 50, 20, 100, 100, 100, 100, 50};
  probRec = {0};
  for (size_t i = 1; i <= probEnemy.size(); i++) {
    probRec.emplace_back(probRec[i - 1] + probEnemy[i - 1]);
  }
  probSum = std::accumulate(probEnemy.begin(), probEnemy.end(), 0);

  enemyLambda.emplace_back([&](Enemy *&enemy) {
    enemy = new BlackWarrior(this, &map->walkingPath);
  });
  enemyLambda.emplace_back(
      [&](Enemy *&enemy) { enemy = new Dragon(this, &map->flyingPath); });
  enemyLambda.emplace_back([&](Enemy *&enemy) {
    enemy = new RobotSoldier(this, &map->walkingPath);
  });
  enemyLambda.emplace_back(
      [&](Enemy *&enemy) { enemy = new Shaman(this, &map->walkingPath); });
  enemyLambda.emplace_back(
      [&](Enemy *&enemy) { enemy = new Spirit(this, &map->walkingPath); });
  enemyLambda.emplace_back([&](Enemy *&enemy) {
    enemy = new FallenWarrior(this, &map->walkingPath);
  });
  enemyLambda.emplace_back(
      [&](Enemy *&enemy) { enemy = new Ghost(this, &map->walkingPath); });

  enemyLambda.emplace_back([&](Enemy *&enemy) {
    if (QRandomGenerator::global()->bounded(0, 15) < 15) {
      QList<QPointF> path;
      path << map->flyingPath.first();
      int pathLen = QRandomGenerator::global()->bounded(5, 15);
      while (pathLen--) {
        // path << Map::BlockToCoordinate(
        //     {QRandomGenerator::global()->bounded(0, 16),
        //      QRandomGenerator::global()->bounded(0, 12)});
        path << QPointF(QRandomGenerator::global()->bounded(0, 1280),
                        QRandomGenerator::global()->bounded(0, 960));
      }
      path << map->flyingPath.last();
      enemy = new CowardPlane(this, &path);
    } else {
      enemy = new CowardPlane(this, &map->flyingPath);
    }
  });

  statistic->enemyNum.setCurValue(0);
  enemyWave(50);
}

Game::~Game() {}

void Game::endThisGame(QString s) {
  if (s == QString("Road Error!")) {
    QMessageBox message(QMessageBox::NoIcon, "Initializing Fail",
                        "Road Error!");
    message.setStyleSheet(
        "QLabel{min-width: 200px;min-height: 100px;}"
        "border-image: url(:/images/messagebox.png);"
        "QWidget{border-top-left-radius:15px;border-top-right-radius:5px;}");

    message.setWindowModality(Qt::NonModal);
    message.setWindowFlags(Qt::FramelessWindowHint);
    message.setWindowOpacity(0.8);
    // message.setMask(QPixmap(":/images/messagebox.png").scaled(200,
    // 100).mask());
    message.addButton("Return", QMessageBox::AcceptRole);
    message.exec();
  } else if (s == QString("GameOver")) {
    advanceTimer.disconnect();
    spawnTimer.disconnect();
    // map->disconnect();

    QMessageBox message(QMessageBox::NoIcon, "Mission Failed", "Game Over😈");
    message.setWindowModality(Qt::NonModal);
    message.resize(200, 50);
    message.addButton("Return", QMessageBox::AcceptRole);
    message.exec();
  }
  // parent->setGame(nullptr);
  deleteLater();
}

void Game::updateGameSpeed() { advanceTimer.start(500 / gameSpeed); }

bool Game::isPaused() const { return !advanceTimer.isActive(); }

void Game::enemyWave(int maxNum) {
  statistic->enemyNum.setMaxValue(maxNum);
  startSpawn();
}

void Game::spawnEnemy() {
  Enemy *enemy = nullptr;
  enemyLambda[randEnemyIndex()](enemy);

  statistic->enemyNum.changeCurValue(1);
  scene.addItem(enemy);
}

void Game::startSpawn(bool force) {
  if (!force && spawnTimer.isActive()) {
    return;
  }
  spawnTimer.start(100000 / spawnSpeed);
}
void Game::stopSpawn() {
  if (spawnTimer.isActive()) {
    spawnTimer.stop();
  }
}

int Game::randEnemyIndex() {
  int index = QRandomGenerator::global()->bounded(0, probSum + 1);
  for (size_t i = 0; i < probRec.size() - 1; i++) {
    if (probRec[i] <= index && index < probRec[i + 1]) {
      return i;
    }
  }
  return 0;
}

void Game::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_N:
    enemyWave(100);
    break;
  case Qt::Key_T:
    enemyWave(200);
    break;
  case Qt::Key_Left:
    gameSpeed = std::max(20, gameSpeed - 10);
    updateGameSpeed();
    break;
  case Qt::Key_Right:
    gameSpeed = std::min(100, gameSpeed + 10);
    updateGameSpeed();
    break;
  case Qt::Key_Up:
    spawnSpeed = std::min(100, spawnSpeed + 10);
    startSpawn(true);
    break;
  case Qt::Key_Down:
    spawnSpeed = std::max(20, spawnSpeed - 10);
    startSpawn(true);
    break;
  case Qt::Key_F5:
    if (advanceTimer.isActive()) {
      advanceTimer.stop();
      statistic->setEnabled(false);
      scene.advance();
    } else {
      statistic->setEnabled(true);
      advanceTimer.start();
    }
    break;
  default:
    event->ignore();
    break;
  }
}

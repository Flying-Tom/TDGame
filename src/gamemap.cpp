// Copyright 2022 Flying-Tom

#include <enemy/enemy.h>
#include <game.h>
#include <gameitem.h>
#include <gamemap.h>
#include <shop.h>
#include <statistic.h>
#include <tower/bomb.h>
#include <tower/campfire.h>
#include <tower/guntower.h>
#include <tower/lasertower.h>
#include <tower/missiletower.h>
#include <tower/repeller.h>
#include <tower/sawtooth.h>
#include <tower/shield.h>
#include <tower/tower.h>

static int blockWidthNumber = 16;
static int blockHeightNumber = 12;

template <typename Val> Val bounded(Val minx, Val x, Val maxx) {
  if (x < minx)
    x = minx;
  else if (x > maxx)
    x = maxx;
  return x;
}

GameMap::GameMap(Game *game, QString *mapConfig)
    : game(game), mapConfig(mapConfig),
      destinationMovie(":/images/startbutton.gif"), towerShadow(nullptr) {
  setAcceptDrops(true);

  loadConfig();

  for (int i = 0; i < road.length() - 1; i++) {
    if (road[i].x() == road[i + 1].x()) {
      for (int y = std::min(road[i].y(), road[i + 1].y()),
               y1 = std::max(road[i].y(), road[i + 1].y()),
               x = bounded(0, road[i].x(), blockWidthNumber);
           y <= y1; y++) {
        isroad[x][bounded(0, y, blockHeightNumber)] = true;
      }
    } else if (road[i].y() == road[i + 1].y()) {
      for (int x = std::min(road[i].x(), road[i + 1].x()),
               x1 = std::max(road[i].x(), road[i + 1].x()),
               y = bounded(0, road[i].y(), blockHeightNumber);
           x <= x1; x++) {
        isroad[bounded(0, x, blockWidthNumber)][y] = true;
      }
    } else {
      game->endThisGame("Road Error!");
    }
  }

  destinationMovie.setSpeed(150);
  destinationMovie.start();
}

GameMap::~GameMap() {
  for (size_t i = 0; i < 17; i++) {
    qDeleteAll(itemoccupied[i]);
    isroad[i].clear();
    isoccupied[i].clear();
    itemoccupied[i].clear();
  }

#ifdef MAPGENERATING
  for (auto i : pointCount)
    std::cout << "(" << i.first << "," << i.second << ")|";
  std::cout << std::endl;
#endif
}

QPoint GameMap::CoordinateToBlock(QPointF p) {
  qreal x = p.x() / 80, y = p.y() / 80;
  return QPoint((qint32)x, (qint32)y);
}

QPointF GameMap::BlockToCoordinate(QPoint p) {
  return QPointF(p.x() * 80 + 40, p.y() * 80 + 40);
}

bool GameMap::IsRoad(QPoint p) { return isroad[p.x()][p.y()]; }

bool GameMap::IsOccupied(QPoint p) { return isoccupied[p.x()][p.y()]; }

QGraphicsItem *GameMap::ItemOccupied(QPoint p) {
  return itemoccupied[p.x()][p.y()];
}

void GameMap::Occupy(QGraphicsItem *item, QPointF pos) {
  QPoint p = CoordinateToBlock(pos);
  itemoccupied[p.x()][p.y()] = item;
  isoccupied[p.x()][p.y()] = true;

#ifdef MAPGENERATING
  pointCount.insert({p.x(), p.y()});
#endif
}

void GameMap::Destory(QPointF pos) {
  QPoint p = CoordinateToBlock(pos);

  isoccupied[p.x()][p.y()] = false;
  itemoccupied[p.x()][p.y()] = nullptr;
}

QRectF GameMap::boundingRect() const { return QRectF(0, 0, width, height); }

void GameMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) {
  Q_UNUSED(painter)
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QPointF destination = BlockToCoordinate(road.last());
  painter->drawImage(
      QRectF(destination.x() - 100, destination.y() - 128, 160, 160),
      destinationMovie.currentImage());

  if (towerShadow) {
    painter->setOpacity(0.6);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(255, 255, 255));
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);
    QRectF r = towerShadow->atkArea->boundingRect();

    painter->drawImage(towerShadowRect, towerShadow->getImage());
    painter->drawEllipse(QRectF(r.x() + towerShadowRect.x() + 40,
                                r.y() + towerShadowRect.y() + 40, r.width(),
                                r.height()));
  }

  if (game->isPaused()) {
    painter->drawImage(QRectF(720 - 64, 480 - 64, 128, 128),
                       QImage(":/images/pause.png"));
  }
}

void GameMap::advance(int phase) {
  if (!phase) {
  } else {
    update();
  }
}

bool GameMap::outofScreen(QGraphicsItem *p) {
  return !(((0 <= p->pos().x()) && (p->pos().x() <= width)) &&
           ((0 <= p->pos().y()) && (p->pos().y() <= height)));
}

void GameMap::mousePressEvent(QGraphicsSceneMouseEvent *event) {
#ifdef MAPGENERATING
  QPoint p = CoordinateToBlock(event->pos());
  pointCount.insert({p.x(), p.y()});
  //    qDebug() << CoordinateToBlock(event->pos()) << "|";
#endif
  event->ignore();
}

void GameMap::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
  if (event->mimeData()->hasText()) {
    event->setAccepted(true);
    update();
  } else {
    event->setAccepted(false);
  }
}

void GameMap::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
  if (event->mimeData()->hasText()) {
    QString s = event->mimeData()->text();
    addTowerShadow(s, event->pos());
#ifdef MAPGENERATING
    if (s == "guntower")
      addTower(s, event->pos());
#endif
  }
}

void GameMap::dropEvent(QGraphicsSceneDragDropEvent *event) {
  if (event->mimeData()->hasText()) {
    QString s = event->mimeData()->text();
    addTower(s, event->pos());
    if (towerShadow) {
      delete towerShadow;
      towerShadow = nullptr;
    }
  }
}

void GameMap::loadConfig() {
  isroad.resize(blockWidthNumber + 1);
  isoccupied.resize(blockWidthNumber + 1);
  itemoccupied.resize(blockWidthNumber + 1);

  for (int i = 0; i < blockWidthNumber + 1; i++) {
    isroad[i].resize(blockHeightNumber + 1);
    isoccupied[i].resize(blockHeightNumber + 1);
    itemoccupied[i].resize(blockHeightNumber + 1);
  }

  QSettings ConfigIni(*mapConfig, QSettings::IniFormat, 0);

  mapImage = QImage(ConfigIni.value("/map/image").toString());

  char buf[65536];
  char *point = nullptr;
  char *save_ptr = NULL;
  memset(buf, '\0', sizeof(buf));
  strncpy(buf,
          ConfigIni.value("/path/walkingPathPoints")
              .toString()
              .toStdString()
              .c_str(),
          sizeof(buf));
  point = strtok_r(buf, "|", &save_ptr);
  while (point != NULL) {
    int x, y;
    sscanf(point, "(%d,%d)", &x, &y);
    road << QPoint(x, y);
    walkingPath << BlockToCoordinate({x, y});
    point = strtok_r(NULL, "|", &save_ptr);
  }

  memset(buf, '\0', sizeof(buf));
  strncpy(buf,
          ConfigIni.value("/path/flyingPathPoints")
              .toString()
              .toStdString()
              .c_str(),
          sizeof(buf));

  point = strtok_r(buf, "|", &save_ptr);
  while (point != NULL) {
    int x, y;
    sscanf(point, "(%d,%d)", &x, &y);
    flyingPath << BlockToCoordinate({x, y});
    point = strtok_r(NULL, "|", &save_ptr);
  }

  memset(buf, '\0', sizeof(buf));
  strncpy(
      buf,
      ConfigIni.value("/landform/obstacles").toString().toStdString().c_str(),
      sizeof(buf));
  point = strtok_r(buf, "|", &save_ptr);
  while (point != NULL) {
    int x, y;
    sscanf(point, "(%d,%d)", &x, &y);
    Occupy(nullptr, BlockToCoordinate({x, y}));
    point = strtok_r(NULL, "|", &save_ptr);
  }
}

void GameMap::addTower(QString s, QPointF pos) {
  QPoint block = CoordinateToBlock(pos);
  if (IsOccupied(block) == false) {
    pos = BlockToCoordinate(block);

    Tower *tower = nullptr;
    switch (Shop::map[s]) {
    case 0:
      tower = new GunTower(this);
      break;
    case 1:
      tower = new LaserTower(this);
      break;
    case 2:
      tower = new Repeller(this);
      break;
    case 3:
      tower = new Bomb(this);
      break;
    case 4:
      tower = new MissileTower(this);
      break;
    case 5:
      tower = new SawTooth(this);
      break;
    case 6:
      tower = new CampFire(this);
      break;
    case 7:
      tower = new Shield(this);
      break;
    default:
      assert(false);
      break;
    }

    if ((tower->getAtkType() == towerAtkType::MELEE &&
         IsRoad(block) == false) ||
        (tower->getAtkType() == towerAtkType::RANGE && IsRoad(block) == true)) {
      delete tower;
      return;
    }

    if (game->statistic.money.getCurValue() >= Shop::cost[Shop::map[s]]) {
      game->statistic.money.changeCurValue(-Shop::cost[Shop::map[s]]);
    } else {
      delete tower;
      return;
    }

    tower->setParentItem(this);
    tower->setPos(pos);
    tower->infopanel.setParentItem(this);
    tower->infopanel.hide();
    Occupy(tower, tower->pos());
  } else {
    Tower *t = qgraphicsitem_cast<Tower *>(ItemOccupied(block));
    if (s == QString("repeller") && t->getName() == QString("repeller")) {
      t->HP.setCurValue(t->HP.getMaxValue());
    }
  }
}

void GameMap::addTowerShadow(QString s, QPointF pos) {
  QPoint block = CoordinateToBlock(pos);
  if (IsOccupied(block) == false) {
    pos = BlockToCoordinate(block);
    if (towerShadow == nullptr) {
      switch (Shop::map[s]) {
      case 0:
        towerShadow = new GunTower(nullptr);
        break;
      case 1:
        towerShadow = new LaserTower(nullptr);
        break;
      case 2:
        towerShadow = new Repeller(nullptr);
        break;
      case 3:
        towerShadow = new Bomb(nullptr);
        break;
      case 4:
        towerShadow = new MissileTower(nullptr);
        break;
      case 5:
        towerShadow = new SawTooth(this);
        break;
      case 6:
        towerShadow = new CampFire(this);
        break;
      case 7:
        towerShadow = new Shield(this);
        break;
      default:
        qDebug() << Shop::map[s];
        assert(false);
        break;
      }
    }

    if ((towerShadow->getAtkType() == towerAtkType::MELEE &&
         IsRoad(block) == true) ||
        (towerShadow->getAtkType() == towerAtkType::RANGE &&
         IsRoad(block) == false)) {
      QRectF r = towerShadow->boundingRect();
      towerShadowRect =
          QRectF(pos.x() + r.x(), pos.y() + r.y(), r.width(), r.height());
    }
  }
}

void GameMap::removeTower(QPointF pos) {
  QPoint block = CoordinateToBlock(pos);
  if (IsOccupied(block) == false)
    return;
  Tower *t = qgraphicsitem_cast<Tower *>(ItemOccupied(block));
  game->statistic.money.changeCurValue(Shop::cost[Shop::map[t->getName()]] / 2);

  Destory(block);
}

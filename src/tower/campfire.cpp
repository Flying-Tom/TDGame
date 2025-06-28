// Copyright 2022 Flying-Tom

#include <tower/bomb.h>
#include <tower/campfire.h>

#include <enemy/enemy.h>

CampFire::CampFire(GameMap *map)
    : Tower(map, GameValue<qreal>(10, 10), RANGE, 250, GameValue<int>(0, 3),
            GameValue<int>(0, 500)),
      movie(":images/campfire.gif") {
  image = QImage(":images/campfire.png");
  movie.start();
}

CampFire::~CampFire() {}

void CampFire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  GameItem::paint(painter, option, widget);
  painter->drawImage(boundingRect(), movie.currentImage());
}

void CampFire::aquireTarget() {
  static int ax[3] = {-80, 0, 80};
  static int ay[3] = {-80, 0, 80};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
      QPoint block(
          GameMap::CoordinateToBlock(QPointF(x() + ax[i], y() + ay[j])));
      if (map->IsOccupied(block) == false && map->IsRoad(block) == true) {
        Tower *tower = new Bomb(map);
        tower->setParentItem(map);
        tower->setPos(QPointF(x() + ax[i], y() + ay[j]));
        tower->infopanel.setParentItem(map);
        tower->infopanel.hide();
        map->Occupy(tower, tower->pos());
        return;
      }
    }
}

void CampFire::advance(int phase) {
  if (!phase) {
    if (HP.getCurValue() == 0) {
      delete this;
      return;
    }
    if (aquireCounter.getCurValue() < aquireCounter.getMaxValue()) {
      aquireCounter.changeCurValue(1);
    } else {
      aquireTarget();
      aquireCounter.setCurValue(0);
    }
  } else {
    update();
  }
}

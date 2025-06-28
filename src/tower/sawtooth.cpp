// Copyright 2022 Flying-Tom

#include <tower/sawtooth.h>

#include <enemy/enemy.h>

SawTooth::SawTooth(GameMap *map)
    : Tower(map, "sawtooth", GameValue<qreal>(500, 500), MELEE, 0,
            GameValue<int>(0, 0)) {
  image = QImage(":images/sawtooth.png");
  angle = 0;
}

SawTooth::~SawTooth() {}

void SawTooth::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->drawImage(boundingRect(), image);
}
void SawTooth::advance(int phase) {
  if (!phase) {
    if (HP.getCurValue() == 0) {
      delete this;
      return;
    }
    setRotation(angle);
    angle += 20;
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.empty()) {
      for (QGraphicsItem *item : items) {
        if (item->type() == Enemy::Type) {
          Enemy *e = qgraphicsitem_cast<Enemy *>(item);
          if (e->getMoveType() == enemyMoveType::WALKING) {
            e->HP.changeCurValue(-0.5);
            e->underAtk = true;
          }
        }
      }
    }
  } else {
    update();
  }
}

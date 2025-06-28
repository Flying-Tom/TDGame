// Copyright 2022 Flying-Tom

#include "tower/tower.h"
#include <bullet/missile.h>
#include <tower/guntower.h>

GunTower::GunTower(GameMap *map)
    : Tower(map, "guntower", GameValue<qreal>(20, 20), RANGE, 400) {
  image = QImage(":images/guntower.png");
  atkTarget = nullptr;
}

GunTower::~GunTower() {}

QRectF GunTower::boundingRect() const { return rectangularModel; }

void GunTower::attack() {
  GunBullet *bullet = new GunBullet(5);

  QPointF atkTargetPos;
  if (atkTarget.isNull()) {
    atkTargetPos = pos();
  } else {
    atkTargetPos = atkTarget->pos();
  }

  QLineF ln(QPointF(x(), y()), atkTargetPos);
  qreal angle = -1 * ln.angle();

  qreal dy = 64 * qSin(qDegreesToRadians(angle));
  qreal dx = 64 * qCos(qDegreesToRadians(angle));
  bullet->setPos(x() + dx, y() + dy);

  setTransformOriginPoint(boundingRect().center());
  setRotation(angle + 90);

  HPMeter->setRotation(-angle - 90);
  atkArea->setRotation(-angle);
  bullet->setRotation(angle);
  scene()->addItem(bullet);
}

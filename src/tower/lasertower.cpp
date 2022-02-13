// Copyright 2022 Flying-Tom

#include <tower/lasertower.h>

LaserTower::LaserTower(GameMap *map)
    : Tower(map, "lasertower", GameValue<qreal>(20, 20), RANGE, 256) {
  trajectory = nullptr;

  image = QImage(":images/lasertower.png");
}

LaserTower::~LaserTower() {
  if (trajectory) delete trajectory;
}

QRectF LaserTower::boundingRect() const { return QRectF(-32, -64, 64, 128); }

void LaserTower::attack() {
  if (trajectory == nullptr) {
    trajectory = new Laser(this, 1);
    scene()->addItem(trajectory);
  }

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
  trajectory->setPos(x() + dx, y() + dy);

  setTransformOriginPoint(boundingRect().center());
  setRotation(angle + 90);

  HPMeter->setRotation(-angle - 90);
  atkArea->setRotation(-angle);
  trajectory->setRotation(angle + 90);
}

Laser *LaserTower::getTrajectory() const { return trajectory; }

void LaserTower::setTrajectory(Laser *newTrajectory) {
  trajectory = newTrajectory;
}

void LaserTower::aquireTarget() {
  QList<QGraphicsItem *> colliding_items = atkArea->collidingItems();

  for (QGraphicsItem *item : colliding_items) {
    Enemy *e = qgraphicsitem_cast<Enemy *>(item);
    if (item->type() == Enemy::Type && e->getMoveType() == Enemy::WALKING &&
        e->getIsDead() == false) {
      atkTarget = e;
      attack();
      return;
    }
  }
}

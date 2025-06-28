// Copyright 2022 Flying-Tom

#include <tower/lasertower.h>

#include <enemy/enemy.h>

LaserTower::LaserTower(GameMap *map)
    : Tower(map, "lasertower", GameValue<qreal>(20, 20), RANGE, 512) {
  trajectory = nullptr;

  image = QImage(":images/lasertower.png");
}

LaserTower::~LaserTower() { delete trajectory; }

QRectF LaserTower::boundingRect() const { return rectangularModel; }

void LaserTower::attack() {
  if (trajectory == nullptr) {
    trajectory = new Laser(this, 0.5);
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
  for (QGraphicsItem *item : atkArea->collidingItems()) {
    Enemy *e = Enemy::castItem(item);
    if (e != nullptr && !e->getIsDead() &&
        e->getMoveType() == EnemyMoveType::WALKING) {
      atkTarget = e;
      attack();
      return;
    }
  }
}

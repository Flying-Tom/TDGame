// Copyright 2022 Flying-Tom

#include <tower/repeller.h>

#include <enemy/enemy.h>

Repeller::Repeller(GameMap *map)
    : Tower(map, GameValue<qreal>(6000, 6000), MELEE, 50,
            GameValue<int>(0, 3)) {
  image = QImage(":images/repeller.png");
}

Repeller::~Repeller() {}

void Repeller::advance(int phase) {
  if (!phase) {
    if (HP.getCurValue() == 0) {
      delete this;
      return;
    }

    // foreach (QGraphicsItem *item, collidingItems()) {
    //   Enemy *e = Enemy::castItem(item);
    //   if (e != nullptr && !e->getIsDead()) {
    //     QLineF ln(e->pos(), e->getPoint(e->getpointIndex() - 1));

    //     qreal length =
    //         (qreal)QRandomGenerator::global()->bounded(5, 8) / 10 *
    //         ln.length();

    //     qreal dy = length * qSin(qDegreesToRadians(-ln.angle()));
    //     qreal dx = length * qCos(qDegreesToRadians(-ln.angle()));

    //     e->setPos(e->pos().x() + dx, e->pos().y() + dy);
    //     e->HP.changeCurValue(-0.5);
    //     HP.changeCurValue(1);
    //   }
    // }
  } else {
    update();
  }
}

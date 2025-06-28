// Copyright 2022 Flying-Tom

#include <tower/missiletower.h>

#include <enemy/enemy.h>

MissileTower::MissileTower(GameMap *map)
    : Tower(map, GameValue<qreal>(5, 5), RANGE, 2048, GameValue<int>(0, 5),
            GameValue<int>(0, 175)) {
  image = QImage(":images/missiletower.png");
}

MissileTower::~MissileTower() {}

void MissileTower::aquireTarget() {
  QList<Enemy *> enemy_list = QList<Enemy *>();

  for (QGraphicsItem *item : atkArea->collidingItems()) {
    Enemy *e = Enemy::castItem(item);
    if (e != nullptr && !e->getIsDead()) {
      enemy_list.append(e);
    }
  }

  if (!enemy_list.empty()) {
    int index = QRandomGenerator::global()->bounded(0, enemy_list.size());
    atkTarget = enemy_list[index];
    attack();
  }
}

void MissileTower::attack() {
  Missile *bullet = new Missile(atkTarget, 50);
  bullet->setPos(pos());
  scene()->addItem(bullet);
}

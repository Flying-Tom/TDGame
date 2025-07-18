// Copyright 2022 Flying-Tom

#include <tower/bomb.h>

#include <enemy/enemy.h>

Bomb::Bomb(GameMap *map)
    : Tower(map, GameValue<qreal>(8, 8), MELEE, 256,
            GameValue<int>(0, 20)),
      movie(":images/bomb.gif") {
  image = QImage(":images/bomb.png");
}

Bomb::~Bomb() {}

void Bomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)

  //    Tower::paint(painter, option, widget);
  GameItem::paint(painter, option, widget);
  if (HP.getCurValue() == 0) {
    painter->drawImage(QRectF(-256, -256, 512, 512), movie.currentImage());
  } else {
    painter->drawImage(boundingRect(), image);
  }
}

void Bomb::advance(int phase) {
  if (!phase) {
    if (HP.getCurValue() == 0) {
      if (movie.state() == QMovie::NotRunning) {
        movie.start();
        bombing();
      } else if (movie.currentFrameNumber() >= movie.frameCount() - 2) {
        delete this;
        return;
      }
    }
  } else {
    update();
  }
}

void Bomb::bombing() {
  for (QGraphicsItem *item : atkArea->collidingItems()) {
    Enemy *e = Enemy::castItem(item);
    if (e != nullptr && !e->getIsDead() &&
        e->getMoveType() == EnemyMoveType::WALKING) {
      e->HP.setCurValue(0);
      return;
    }

    Tower *t = Tower::castItem(item);
    if (t != nullptr && !t->getIsDead() &&
        t->getAtkType() == TowerAtkType::MELEE) {
      e->HP.setCurValue(0);
      return;
      // QString eName = e->getName();
      // if (eName == "bomb" || eName == "repeller") {
      //   e->HP.setCurValue(0);
      // }
    }
  }
}

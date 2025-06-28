// Copyright 2022 Flying-Tom

#include <enemy/cowardplane.h>

#include <bullet/bullet.h>
#include <tower/tower.h>

CowardPlane::CowardPlane(Game *game, QList<QPointF> *path)
    : Enemy(game, path, 100, GameValue<qreal>(500, 500),
            GameValue<qreal>(500, 500), GameValue<qreal>(1.5, 6),
            EnemyMoveType::FLYING, 200) {
  movie.setFileName(":/images/cowardplane.gif");
  movie.start();

  canAttackMelee = false;
  canAttackRange = true;
}

QPainterPath CowardPlane::shape() const {
  QPainterPath path;
  path.addRect(QRectF(-20, -25, 60, 60));
  return path;
}

void CowardPlane::advance(int phase) {
  if (!phase) {
    if (HP.getCurValue() <= 0) {
      isDead = true;
      speed.setCurValue(0);

      if (deathCounter.getCurValue() < deathCounter.getMaxValue()) {
        deathCounter.changeCurValue(1);
      } else {
        game->statistic->money.changeCurValue(money);
        delete this;
        return;
      }
      return;
    }

    for (QGraphicsItem *item : atkArea->collidingItems()) {
      Tower *t = Tower::castItem(item);
      if (t != nullptr && t->getAtkType() == TowerAtkType::RANGE) {
        speed.setCurValue(4.5);
        movie.setSpeed(450);
        moveForward();
        return;
      }

      Bullet *b = Bullet::castItem(item);
      if (b != nullptr) {
        speed.setCurValue(4.5);
        movie.setSpeed(450);
        moveForward();
        return;
      }
    }

    speed.setCurValue(1.5);
    movie.setSpeed(150);
    moveForward();
  } else {
    update();
  }
}

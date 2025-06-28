// Copyright 2022 Flying-Tom

#include <enemy/cowardplane.h>

#include <bullet/bullet.h>
#include <tower/tower.h>

CowardPlane::CowardPlane(Game *game, QList<QPointF> *path)
    : Enemy(game, path, 100, GameValue<qreal>(500, 500),
            GameValue<qreal>(500, 500), GameValue<qreal>(1.5, 6),
            enemyMoveType::FLYING, 200) {
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
    if (HP.getCurValue() == 0) {
      isDead = true;
      speed.setCurValue(0);

      if (deathCounter.getCurValue() < deathCounter.getMaxValue()) {
        deathCounter.changeCurValue(1);
      } else {
        game->statistic.money.changeCurValue(money);
        delete this;
        return;
      }
      return;
    }

    QList<QGraphicsItem *> colliding_items = atkArea->collidingItems();
    for (QGraphicsItem *item : colliding_items) {
      if (item->type() == GameItemType::TOWER) {
        Tower *t = qgraphicsitem_cast<Tower *>(item);
        if (t->getAtkType() == towerAtkType::RANGE) {
          speed.setCurValue(4.5);
          movie.setSpeed(450);
          moveForward();
          return;
        }
      }
      if (item->type() == GameItemType::BULLET) {
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

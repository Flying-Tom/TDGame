// Copyright 2022 Flying-Tom

#include <enemy/shaman.h>

Shaman::Shaman(Game *game, QList<QPointF> *path)
    : Enemy(game, path, 50, GameValue<qreal>(200, 200),
            GameValue<qreal>(100, 100), GameValue<qreal>(1, 100),
            EnemyMoveType::WALKING, 150) {
  movie.setFileName(":/images/shaman.gif");
  movie.start();

  atkMovie.setFileName(":/images/shamanattack.gif");
  atkMovie.start();
  atkMovieRect.setWidth(160);
  atkMovieRect.setHeight(160);

  canAttackMelee = true;
  canAttackRange = false;
}

void Shaman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
  if (atkTarget.isNull() == false) {
    atkMovieRect.setRect(atkTarget->x() - x() - atkMovieRect.width() / 2,
                         atkTarget->y() - y() - atkMovieRect.height() / 2, 160,
                         160);
  }
  Enemy::paint(painter, option, widget);
}

QPainterPath Shaman::shape() const {
  QPainterPath path;
  path.addRect(boundingRect());
  return path;
}

void Shaman::aquireTarget() {
  for (QGraphicsItem *item : atkArea->collidingItems()) {
    Enemy *e = Enemy::castItem(item);
    if (e != nullptr && !e->getIsDead() &&
        e->HP.getCurValue() < e->HP.getMaxValue()) {
      atkTarget = e;
      break;
    }
  }

  if (atkTarget.isNull()) {
    isStopped = false;
  } else {
    // atkMoiveRect.setRect(atkTarget->x() - x() - atkMoiveRect.width() / 2,
    //     atkTarget->y() - y() - atkMoiveRect.height() / 2,
    //     atkMoiveRect.width(),
    //     atkMoiveRect.height());
    // isStopped = true;
    // qDebug() << "hasTarget";
  }
}

void Shaman::attack() {
  if (atkTarget->getIsDead() == false &&
      atkMovie.currentFrameNumber() == atkMovie.frameCount() - 1) {
    if (atkTarget != this) {
      speed.setCurValue(atkTarget->speed.getCurValue());
      Enemy *e = Enemy::castItem(atkTarget.data());
      // follow the target
      if (e != nullptr && !e->getIsDead()) {
        isStopped = e->getIsStopped();
      }
    }
    atkTarget->HP.changeCurValue(atk.getCurValue());
    atkMovie.jumpToNextFrame();
    atkTarget.clear();
  }
}

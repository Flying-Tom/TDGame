// Copyright 2022 Flying-Tom

#include <enemy/dragon.h>

#include <tower/tower.h>

Dragon::Dragon(Game *game, QList<QPointF> *path)
    : Enemy(game, path, 300, GameValue<qreal>(700, 700),
            GameValue<qreal>(15, 15), GameValue<qreal>(0.3, 0.3),
            EnemyMoveType::FLYING, 100) {
  movie.setFileName(":/images/dragon.gif");
  movie.start();

  atkMovie.setFileName(":/images/dragonfire.gif");
  atkMovie.start();
  atkMovieRect.setWidth(160);
  atkMovieRect.setHeight(160);

  canAttackMelee = true;
  canAttackRange = true;
}

Dragon::~Dragon() {}

QRectF Dragon::boundingRect() const { return QRectF(-128, -200, 256, 256); }

QPainterPath Dragon::shape() const {
  QPainterPath path;
  path.addRect(QRectF(-64, -64, 128, 128));
  return path;
}

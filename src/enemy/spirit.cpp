// Copyright 2022 Flying-Tom

#include <enemy/spirit.h>

Spirit::Spirit(Game *game, QList<QPointF> *path)
    : Enemy(game, path, 50, GameValue<qreal>(500, 500),
            GameValue<qreal>(100, 100), GameValue<qreal>(1, 1),
            EnemyMoveType::WALKING, 100) {
  movie.setFileName(":/images/spirit.gif");
  movie.start();

  atkMovie.setFileName(":/images/spiritattack.gif");
  atkMovie.start();
  atkMovieRect.setWidth(160);
  atkMovieRect.setHeight(160);

  canAttackMelee = true;
  canAttackRange = false;
}

QRectF Spirit::boundingRect() const { return QRectF(-80, -80, 160, 160); }

QPainterPath Spirit::shape() const {
  QPainterPath path;
  path.addRect(QRectF(-40, -40, 80, 80));
  return path;
}

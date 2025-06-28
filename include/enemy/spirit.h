// Copyright 2022 Flying-Tom
#ifndef INCLUDE_ENEMY_SPIRIT_H_
#define INCLUDE_ENEMY_SPIRIT_H_

#include <enemy/enemy.h>

class Spirit : public Enemy {
public:
  Spirit(Game *game, QList<QPointF> *path);
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
};

#endif // INCLUDE_ENEMY_SPIRIT_H_

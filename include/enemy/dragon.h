// Copyright 2022 Flying-Tom
#ifndef INCLUDE_ENEMY_DRAGON_H_
#define INCLUDE_ENEMY_DRAGON_H_

#include <enemy/enemy.h>
#include <game.h>

class Dragon : public Enemy {
public:
  Dragon(Game *game, QList<QPointF> *path);
  ~Dragon();

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
};

#endif // INCLUDE_ENEMY_DRAGON_H_

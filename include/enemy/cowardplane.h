// Copyright 2022 Flying-Tom
#ifndef INCLUDE_ENEMY_COWARDPLANE_H_
#define INCLUDE_ENEMY_COWARDPLANE_H_

#include <enemy/enemy.h>
#include <game.h>

class CowardPlane : public Enemy {
public:
  explicit CowardPlane(Game *game, QList<QPointF> *path);

  QPainterPath shape() const override;
  void advance(int phase) override;
};

#endif //  INCLUDE_ENEMY_COWARDPLANE_H_

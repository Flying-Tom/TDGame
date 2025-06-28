// Copyright 2022 Flying-Tom
#ifndef INCLUDE_ENEMY_BLACKWARRIOR_H_
#define INCLUDE_ENEMY_BLACKWARRIOR_H_

#include <enemy/enemy.h>
#include <game.h>

class BlackWarrior : public Enemy {
public:
  BlackWarrior(Game *game, QList<QPointF> *path);
  QPainterPath shape() const override;
};

#endif // INCLUDE_ENEMY_BLACKWARRIOR_H_

// Copyright 2022 Flying-Tom
#ifndef INCLUDE_ENEMY_GHOST_H_
#define INCLUDE_ENEMY_GHOST_H_

#include <enemy/enemy.h>

class Ghost : public Enemy {
public:
  explicit Ghost(Game *game, QList<QPointF> *path);
  //    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
  //    QWidget *widget) override;
  QPainterPath shape() const override;
};

#endif // INCLUDE_ENEMY_GHOST_H_

// Copyright 2022 Flying-Tom
#ifndef INCLUDE_ENEMY_SHAMAN_H_
#define INCLUDE_ENEMY_SHAMAN_H_

#include <enemy/enemy.h>

class Shaman : public Enemy {
 public:
  Shaman(Game* game, QList<QPointF>* path);
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;
  QPainterPath shape() const override;
  void aquireTarget() override;
  void attack() override;
};

#endif  // INCLUDE_ENEMY_SHAMAN_H_

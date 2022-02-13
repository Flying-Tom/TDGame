// Copyright 2022 Flying-Tom
#ifndef INCLUDE_ENEMY_FALLENWARRIOR_H_
#define INCLUDE_ENEMY_FALLENWARRIOR_H_

#include <enemy/enemy.h>

class FallenWarrior : public Enemy {
 public:
  FallenWarrior(Game* game, QList<QPointF>* path);
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;
  void advance(int phase) override;

  void attack() override;
};

#endif  // INCLUDE_ENEMY_FALLENWARRIOR_H_

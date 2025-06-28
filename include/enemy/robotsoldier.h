// Copyright 2022 Flying-Tom
#ifndef INCLUDE_ENEMY_ROBOTSOLDIER_H_
#define INCLUDE_ENEMY_ROBOTSOLDIER_H_

#include <enemy/enemy.h>

class RobotSoldier : public Enemy {
public:
  explicit RobotSoldier(Game *game, QList<QPointF> *path);
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;

  void attack() override;

protected:
  qreal atkSpeed;
};

#endif // INCLUDE_ENEMY_ROBOTSOLDIER_H_

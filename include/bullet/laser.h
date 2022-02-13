// Copyright 2022 Flying-Tom
#ifndef INCLUDE_BULLET_LASER_H_
#define INCLUDE_BULLET_LASER_H_

#include <bullet/bullet.h>
#include <enemy/enemy.h>

class Laser : public Bullet {
 public:
  Laser(GameItem* parent, qreal atk);
  ~Laser();
  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;
  void advance(int phase) override;

 protected:
  GameItem* parent;
  int counter;
};

#endif  // INCLUDE_BULLET_LASER_H_

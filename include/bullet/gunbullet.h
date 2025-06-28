// Copyright 2022 Flying-Tom
#ifndef INCLUDE_BULLET_GUNBULLET_H_
#define INCLUDE_BULLET_GUNBULLET_H_

#include <bullet/bullet.h>

class GunBullet : public Bullet {
public:
  explicit GunBullet(qreal atk);
  ~GunBullet() override;

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void advance(int phase) override;

  void moveForward() override;
};

#endif // INCLUDE_BULLET_GUNBULLET_H_

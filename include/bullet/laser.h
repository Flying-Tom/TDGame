// Copyright 2022 Flying-Tom
#ifndef INCLUDE_BULLET_LASER_H_
#define INCLUDE_BULLET_LASER_H_

#include <bullet/bullet.h>

class Laser : public Bullet {
public:
  explicit Laser(QPointer<GameItem> parent, qreal atk);
  ~Laser() override;

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void advance(int phase) override;

protected:
  QPointer<GameItem> parent;
  int counter;
};

#endif // INCLUDE_BULLET_LASER_H_

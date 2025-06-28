// Copyright 2022 Flying-Tom
#ifndef INCLUDE_BULLET_MISSILE_H_
#define INCLUDE_BULLET_MISSILE_H_

#include <bullet/bullet.h>

class Missile : public Bullet {
public:
  explicit Missile(QPointer<GameItem> atkTarget, qreal atk);
  ~Missile() override;

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void advance(int phase) override;

  void moveForward() override;
  void bombing();

private:
  QPointer<GameItem> atkTarget;
  qreal atkAngle;

  QGraphicsEllipseItem *bombArea;
  bool isBombing;
  qreal bombRadius;
  QMovie movie;
};

#endif // INCLUDE_BULLET_MISSILE_H_

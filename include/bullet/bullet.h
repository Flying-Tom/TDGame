// Copyright 2022 Flying-Tom
#ifndef INCLUDE_BULLET_BULLET_H_
#define INCLUDE_BULLET_BULLET_H_

#include <gameitem.h>

class Bullet : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

public:
  explicit Bullet();
  virtual ~Bullet();

  enum { Type = GameItemType::BULLET };
  int type() const override;
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void advance(int phase) override;

  virtual void moveForward();

  static Bullet *castItem(QGraphicsItem *gi);

protected:
  QImage image;
  qreal atk;
  qreal speed;
};

#endif // INCLUDE_BULLET_BULLET_H_

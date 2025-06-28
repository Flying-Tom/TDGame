// Copyright 2022 Flying-Tom
#ifndef INCLUDE_SHOP_H_
#define INCLUDE_SHOP_H_

#include <common.h>

class Shop : public QGraphicsItem {
public:
  int counter;

  qreal aleft, atop, awidth, aheight;

  QString towername;
  Shop(QString s, qreal left, qreal top, qreal width, qreal height);
  static const QMap<QString, int> map;
  static const QVector<QString> name;
  static const QVector<int> cost;
  static const QVector<int> cdtime;
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void advance(int phase) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // INCLUDE_SHOP_H_

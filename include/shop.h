// Copyright 2022 Flying-Tom
#ifndef INCLUDE_SHOP_H_
#define INCLUDE_SHOP_H_

#include <common.h>

class ShopItem {
public:
  QString name;
  int cost;
  int cdtime;
};

class Shop {
public:
  Shop(Game *game);
  ~Shop() = default;

  QVector<ShopItem> shopItems;
  QMap<QString, ShopItem> shopItemsMap;
  QMap<QString, int> orderMap;
};

class ShopIcon : public QGraphicsItem {
  Shop *shop;

public:
  ShopIcon(Shop *shop, QString s, qreal left, qreal top, qreal width,
           qreal height);

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void advance(int phase) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public:
  int counter;

  qreal aleft, atop, awidth, aheight;

  QString towername;
};

#endif // INCLUDE_SHOP_H_

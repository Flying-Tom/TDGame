// Copyright 2022 Flying-Tom
#ifndef INCLUDE_TOWER_INFOPANEL_H_
#define INCLUDE_TOWER_INFOPANEL_H_

#include <common.h>
#include <gameitem.h>

class InfoPanel : public QGraphicsItem {
  Q_INTERFACES(QGraphicsItem)
public:
  explicit InfoPanel(GameItem *parent = 0);
  ~InfoPanel();
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void advance(int phase) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  GameItem *parent;
};

#endif // INCLUDE_TOWER_INFOPANEL_H_

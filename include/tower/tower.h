// Copyright 2022 Flying-Tom
#ifndef INCLUDE_TOWER_TOWER_H_
#define INCLUDE_TOWER_TOWER_H_

#include <common.h>
#include <enemy/enemy.h>
#include <gameitem.h>
#include <tower/infopanel.h>

class Tower : public GameItem {
  Q_INTERFACES(QGraphicsItem)

 public:
  enum towerAtkType {
    MELEE = 0,
    RANGE = 1,
  };
  Tower(GameMap* map, QString name = QString(),
        GameValue<qreal> HP = GameValue<qreal>(), int atkType = RANGE,
        qreal atkRadius = 0, GameValue<int> blockNumber = GameValue<int>(0, 3),
        GameValue<int> aquireCounter = GameValue<int>(0, 5));
  ~Tower();
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;
  void advance(int phase) override;

 public:
  enum { Type = UserType + 3 };
  int type() const override;

  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

 protected:
  GameMap* map;
  int atkType;
  QImage image;

 public:
  InfoPanel infopanel;
  void aquireTarget() override;
  void attack() override;
  int getAtkType() const;
  QImage getImage() const;
};

#endif  // INCLUDE_TOWER_TOWER_H_

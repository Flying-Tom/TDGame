// Copyright 2022 Flying-Tom
#ifndef INCLUDE_TOWER_CAMPFIRE_H_
#define INCLUDE_TOWER_CAMPFIRE_H_

#include <tower/tower.h>

class CampFire : public Tower {
public:
  explicit CampFire(GameMap *map);
  ~CampFire();

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  int angle;
  void aquireTarget() override;
  void advance(int phase) override;

  QString name = "campfire";
  QMovie movie;
};

#endif // INCLUDE_TOWER_CAMPFIRE_H_

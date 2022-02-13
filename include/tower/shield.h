// Copyright 2022 Flying-Tom
#ifndef INCLUDE_TOWER_SHIELD_H_
#define INCLUDE_TOWER_SHIELD_H_

#include <tower/tower.h>

class Shield : public Tower {
 public:
  explicit Shield(GameMap* map);
  ~Shield();
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;
  void advance(int phase) override;
};

#endif  // INCLUDE_TOWER_SHIELD_H_

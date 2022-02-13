// Copyright 2022 Flying-Tom
#ifndef INCLUDE_TOWER_GUNTOWER_H_
#define INCLUDE_TOWER_GUNTOWER_H_

#include <bullet/gunbullet.h>
#include <tower/tower.h>

class GunTower : public Tower {
 public:
  explicit GunTower(GameMap* map);
  ~GunTower();
  QRectF boundingRect() const override;

 public:
  void attack() override;
};

#endif  // INCLUDE_TOWER_GUNTOWER_H_

// Copyright 2022 Flying-Tom
#ifndef INCLUDE_TOWER_LASERTOWER_H_
#define INCLUDE_TOWER_LASERTOWER_H_

#include <bullet/laser.h>

#include <tower/tower.h>

class LaserTower : public Tower {
 public:
  explicit LaserTower(GameMap* map);
  ~LaserTower();
  QRectF boundingRect() const override;

  void attack() override;

  Laser* getTrajectory() const;
  void setTrajectory(Laser* newTrajectory);

 protected:
  int prevAngle;
  Laser* trajectory;

 public:
  void aquireTarget() override;
};

#endif  // INCLUDE_TOWER_LASERTOWER_H_

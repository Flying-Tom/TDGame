// Copyright 2022 Flying-Tom
#ifndef INCLUDE_TOWER_MISSILETOWER_H_
#define INCLUDE_TOWER_MISSILETOWER_H_

#include <bullet/missile.h>
#include <tower/tower.h>

class MissileTower : public Tower {
public:
  explicit MissileTower(GameMap *map);
  ~MissileTower();

  QString name = "missiletower";
  void aquireTarget() override;
  void attack() override;
};

#endif // INCLUDE_TOWER_MISSILETOWER_H_

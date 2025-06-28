// Copyright 2022 Flying-Tom
#ifndef INCLUDE_TOWER_REPELLER_H_
#define INCLUDE_TOWER_REPELLER_H_

#include <tower/tower.h>

class Repeller : public Tower {
public:
  explicit Repeller(GameMap *map);
  ~Repeller();
  void advance(int phase) override;
};

#endif // INCLUDE_TOWER_REPELLER_H_

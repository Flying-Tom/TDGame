// Copyright 2022 Flying-Tom
#ifndef INCLUDE_TOWER_SAWTOOTH_H_
#define INCLUDE_TOWER_SAWTOOTH_H_

#include <tower/tower.h>

class SawTooth : public Tower {
 public:
  explicit SawTooth(GameMap* map);
  ~SawTooth();
  void advance(int phase) override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;
  int angle;
};

#endif  // INCLUDE_TOWER_SAWTOOTH_H_

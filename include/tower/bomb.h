// Copyright 2022 Flying-Tom
#ifndef INCLUDE_TOWER_BOMB_H_
#define INCLUDE_TOWER_BOMB_H_

#include <tower/tower.h>

class Bomb : public Tower {
 public:
  explicit Bomb(GameMap* map);
  ~Bomb();
  void advance(int phase) override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;
  void bombing();

 protected:
  QMovie movie;
};

#endif  // INCLUDE_TOWER_BOMB_H_

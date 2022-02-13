// Copyright 2022 Flying-Tom
#ifndef INCLUDE_STATISTIC_H_
#define INCLUDE_STATISTIC_H_

#include <common.h>

class Statistic : public QGraphicsObject {
  Q_OBJECT
 public:
  explicit Statistic(Game* game);
  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;
  void advance(int phase) override;

 public:
  Game* game;
  GameValue<int> life;
  GameValue<int> money;
  GameValue<int> moneyAddCounter;
  int FPS;
  static int frameCount;
  QImage shopBackground;
  QImage lifeIcon;
  QImage coinIcon;
};

#endif  // INCLUDE_STATISTIC_H_

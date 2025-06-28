// Copyright 2022 Flying-Tom
#ifndef INCLUDE_TOWER_TOWER_H_
#define INCLUDE_TOWER_TOWER_H_

#include <gameitem.h>
#include <tower/infopanel.h>

class Tower : public GameItem {
  Q_INTERFACES(QGraphicsItem)

public:
  explicit Tower(GameMap *map, GameValue<qreal> HP = GameValue<qreal>(),
                 int atkType = RANGE, qreal atkRadius = 0,
                 GameValue<int> blockNumber = GameValue<int>(0, 3),
                 GameValue<int> aquireCounter = GameValue<int>(0, 5));
  virtual ~Tower();

  enum { Type = GameItemType::TOWER };
  int type() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void advance(int phase) override;
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

  InfoPanel infopanel;
  void aquireTarget() override;
  void attack() override;
  int getAtkType() const;
  QImage getImage() const;

  static Tower *castItem(QGraphicsItem *gi);

protected:
  GameMap *map;
  int atkType;
  QImage image;
};

const QRectF rectangularModel(-32, -64, 64, 128);

#endif // INCLUDE_TOWER_TOWER_H_

// Copyright 2022 Flying-Tom
#ifndef INCLUDE_GAMEITEM_H_
#define INCLUDE_GAMEITEM_H_

#include <common.h>
#include <qgraphicsitem.h>

enum GameItemType {
  BARE = QGraphicsItem::UserType + 256,
  ENEMY,
  TOWER,
  BULLET,
};

enum EnemyMoveType {
  WALKING = 0,
  FLYING = 1,
};

enum TowerAtkType {
  MELEE = 0,
  RANGE = 1,
};

class GameItem : public QGraphicsObject {
public:
  GameItem();
  virtual ~GameItem();

public:
  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

  virtual void aquireTarget() = 0;
  virtual void attack() = 0;

  virtual bool getIsDead() const;
  virtual void setIsDead(bool newIsDead);

  QPointer<GameItem> getAtkTarget() const;
  void setAtkTarget(QPointer<GameItem> newAtkTarget);

  const QString &getName() const;
  void setName(const QString &newName);

  GameValue<qreal> HP;
  GameValue<qreal> atk;
  GameValue<qreal> speed;
  GameValue<int> blockNumber;
  GameValue<int> aquireCounter;
  QGraphicsEllipseItem *atkArea;
  QGraphicsRectItem *HPMeter;
  bool underAtk;
  GameValue<int> blinkCounter;

  bool isTower();
  bool isEnemy();
  bool isBullet();

protected:
  QString name;

  int money;
  qreal atkRadius;
  bool isDead;

  QPointer<GameItem> atkTarget;
};

#endif // INCLUDE_GAMEITEM_H_

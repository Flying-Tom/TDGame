// Copyright 2022 Flying-Tom
#ifndef INCLUDE_ENEMY_ENEMY_H_
#define INCLUDE_ENEMY_ENEMY_H_

#include <common.h>
#include <game.h>
#include <gameitem.h>
#include <tower/tower.h>

class Enemy : public GameItem {
  Q_INTERFACES(QGraphicsItem)

public:
  enum enemyMoveType {
    WALKING = 0,
    FLYING = 1,
  };
  Enemy(Game *game, QList<QPointF> *path, int money = 0,
        GameValue<qreal> HP = GameValue<qreal>(),
        GameValue<qreal> atk = GameValue<qreal>(),
        GameValue<qreal> speed = GameValue<qreal>(), int moveType = WALKING,
        qreal atkRadius = 0);
  ~Enemy();
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void advance(int phase) override;
  enum { Type = UserType + 2 };
  int type() const override;

  /* enemy actions*/
  void aquireTarget() override;
  void attack() override;
  void moveForward();

  /*setter and getter*/
  QPointF getPoint(int index) const;
  QPointF getDest() const;
  int getpointIndex();
  int getMoveType() const;
  bool getIsStopped() const;
  void setIsStopped(bool newIsStopped);

protected:
  Game *game;
  QList<QPointF> points;
  QPointF dest;
  int pointIndex;

  int moveType;
  bool isStopped;

  bool canAttackMelee;
  bool canAttackRange;

  QMovie movie;
  QMovie atkMovie;
  QRectF atkMovieRect;

  //    int deathCounter;
  GameValue<int> deathCounter;
};

#endif // INCLUDE_ENEMY_ENEMY_H_

// Copyright 2022 Flying-Tom
#ifndef INCLUDE_ENEMY_ENEMY_H_
#define INCLUDE_ENEMY_ENEMY_H_

#include <game.h>
#include <gameitem.h>

class Enemy : public GameItem {
  Q_INTERFACES(QGraphicsItem)

public:
  explicit Enemy(Game *game, QList<QPointF> *path, int money = 0,
                 GameValue<qreal> HP = GameValue<qreal>(),
                 GameValue<qreal> atk = GameValue<qreal>(),
                 GameValue<qreal> speed = GameValue<qreal>(),
                 int moveType = WALKING, qreal atkRadius = 0);
  virtual ~Enemy();

  enum { Type = GameItemType::ENEMY };
  int type() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void advance(int phase) override;

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
  static Enemy *castItem(QGraphicsItem *gi);

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

  GameValue<int> deathCounter;
};

#endif // INCLUDE_ENEMY_ENEMY_H_

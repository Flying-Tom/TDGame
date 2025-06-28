// Copyright 2022 Flying-Tom
#ifndef INCLUDE_GAMEMAP_H_
#define INCLUDE_GAMEMAP_H_

#include <common.h>

#include <set>
#include <utility>

class GameMap : public QGraphicsObject {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

public:
  GameMap(Game *game, QString *mapConfig);
  ~GameMap();
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void advance(int phase) override;

  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
  void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;

public:
  Game *game;
  Shop *shop;
  QString *mapConfig;
  QImage mapImage;
  QList<QPoint> road;
  QList<QPointF> walkingPath;
  QList<QPointF> flyingPath;
  void loadConfig();
  void addTower(QString s, QPointF pos);
  void addTowerShadow(QString s, QPointF pos);
  void removeTower(QPointF pos);

  bool IsRoad(QPoint p);
  bool IsOccupied(QPoint p);
  void Occupy(QGraphicsItem *item, QPointF pos);
  QGraphicsItem *ItemOccupied(QPoint p);
  void Destory(QPointF pos);

private:
  QVector<QVector<bool>> isroad;
  QVector<QVector<bool>> isoccupied;
  QVector<QVector<QGraphicsItem *>> itemoccupied;
  QMovie destinationMovie;
  Tower *towerShadow;
  QRectF towerShadowRect;
  std::set<std::pair<int, int>> pointCount;

public:
  static QPoint CoordinateToBlock(QPointF p);
  static QPointF BlockToCoordinate(QPoint p);
  static const int width = 1280;
  static const int height = 960;
  static bool outofScreen(QGraphicsItem *p);
};

#endif // INCLUDE_GAMEMAP_H_

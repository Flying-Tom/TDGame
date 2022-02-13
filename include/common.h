// Copyright 2022 Flying-Tom
#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

class GameItem;
class Enemy;
class Tower;
class GameMap;
class InfoPanel;
class Game;
class MainWindow;

#include <qmath.h>
#include <string.h>

#include <QDebug>
#include <QFile>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QImage>
#include <QKeyEvent>
#include <QLineF>
#include <QList>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMimeData>
#include <QMovie>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QPointF>
#include <QRandomGenerator>
#include <QSettings>
#include <QString>
#include <QTimer>
#include <QVector>
#include <QtWidgets>
#include <iostream>

template <typename Val>
class GameValue {
 private:
  Val curValue;
  Val maxValue;

 public:
  GameValue() {
    curValue = Val();
    maxValue = Val();
  }
  GameValue(Val cur, Val max) {
    curValue = cur;
    maxValue = max;
  }
  ~GameValue() {}
  inline const Val& getCurValue() const { return curValue; }
  inline void setCurValue(const Val& newCurValue) {
    curValue = newCurValue;
    if (curValue < Val()) curValue = Val();
    if (curValue > maxValue) curValue = maxValue;
  }
  inline void changeCurValue(Val delta) { setCurValue(curValue + delta); }
  inline const Val& getMaxValue() const { return maxValue; }
  inline void setMaxValue(const Val& newMaxValue) { maxValue = newMaxValue; }
};

class InfoMsg : public QWidget {
 public:
  explicit InfoMsg(QWidget* parent) : QWidget(parent) {}
  void paintEvent(QPaintEvent* e) override {
    Q_UNUSED(e)
    QPainter p(this);
    p.drawImage(QRectF(-10, -10, 358, 242), QImage(":/images/messagebox.png"));
  };
};

#endif  // INCLUDE_COMMON_H_

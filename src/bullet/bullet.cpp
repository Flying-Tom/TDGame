// Copyright 2022 Flying-Tom

#include <bullet/bullet.h>

#include <game.h>

Bullet::Bullet() : QObject(), QGraphicsItem() {}
Bullet::~Bullet() {}

QRectF Bullet::boundingRect() const { return QRectF(-8, -8, 16, 16); }

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  Q_UNUSED(painter)
}

void Bullet::advance(int phase) {
  if (!phase) {
  } else {
    update();
  }
}

int Bullet::type() const { return Type; }

void Bullet::moveForward() {}

Bullet *Bullet::castItem(QGraphicsItem *gi) {
  if (gi->type() == GameItemType::BULLET) {
    return qgraphicsitem_cast<Bullet *>(gi);
  }
  return nullptr;
}
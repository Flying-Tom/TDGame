// Copyright 2022 Flying-Tom

#include <bullet/gunbullet.h>

GunBullet::GunBullet(qreal atk) {
  Bullet::atk = atk;
  image = QImage(":images/gunbullet.png");
  speed = 10;
}

QRectF GunBullet::boundingRect() const { return QRectF(-6, -6, 12, 12); }

void GunBullet::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                      QWidget* widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)

  painter->drawImage(boundingRect(), image);
}

void GunBullet::advance(int phase) {
  if (!phase) {
    if (GameMap::outofScreen(this)) {
      delete this;
      return;
    }
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.empty()) {
      for (QGraphicsItem* item : items) {
        if (item->type() == Enemy::Type) {
          Enemy* e = qgraphicsitem_cast<Enemy*>(item);
          e->HP.changeCurValue(-atk);
          e->underAtk = true;
          delete this;
          return;
        }
      }
    }
    moveForward();
  }
}

void GunBullet::moveForward() {
  qreal theta = rotation();

  qreal dy = speed * qSin(qDegreesToRadians(theta));
  qreal dx = speed * qCos(qDegreesToRadians(theta));

  setPos(x() + dx, y() + dy);
}

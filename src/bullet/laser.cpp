// Copyright 2022 Flying-Tom

#include <bullet/laser.h>

#include <enemy/enemy.h>
#include <tower/lasertower.h>

Laser::Laser(QPointer<GameItem> parent, qreal atk) : parent(parent) {
  Bullet::atk = atk;
  counter = 0;
  image = QImage(":images/laser.png");
}

Laser::~Laser() {
  LaserTower *t = qgraphicsitem_cast<LaserTower *>(parent);
  t->setTrajectory(nullptr);
}

QRectF Laser::boundingRect() const { return QRectF(-32, -220, 64, 256); }

void Laser::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->drawImage(boundingRect(), image);
  // painter->drawRect(boundingRect());
}

void Laser::advance(int phase) {
  Bullet::advance(phase);
  if (!phase) {
    bool selfdestroy = true;
    for (QGraphicsItem *item : collidingItems()) {
      Enemy *e = Enemy::castItem(item);
      if (e != nullptr) {
        e->HP.changeCurValue(-atk);
        e->underAtk = true;
        if (e->HP.getCurValue() > 0) {
          selfdestroy = false;
        }
      }
    }

    if (selfdestroy == true) {
      delete this;
      return;
    }
  }
}

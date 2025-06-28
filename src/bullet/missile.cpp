// Copyright 2022 Flying-Tom

#include <bullet/missile.h>

#include <enemy/enemy.h>

Missile::Missile(QPointer<GameItem> atkTarget, qreal atk)
    : atkTarget(atkTarget), bombArea(nullptr), isBombing(false),
      movie(":images/bomb.gif") {
  Bullet::atk = atk;
  image = QImage(":images/missile.png");
  speed = 6;
  bombRadius = 128;
}

Missile::~Missile() {
  if (bombArea)
    delete bombArea;
}

QRectF Missile::boundingRect() const { return QRectF(-40, -20, 80, 40); }

QPainterPath Missile::shape() const {
  QPainterPath path;
  path.addRect(QRectF(-5, -5, 10, 10));
  return path;
}

void Missile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)

  if (isBombing) {
    painter->drawImage(bombArea->boundingRect(), movie.currentImage());
  } else {
    painter->drawImage(boundingRect(), image);
    // painter->drawPath(shape());
  }
}

void Missile::advance(int phase) {
  Bullet::advance(phase);
  if (!phase) {
    if (GameMap::outofScreen(this)) {
      delete this;
      return;
    }
    if (isBombing) {
      if (movie.state() == QMovie::NotRunning) {
        movie.start();
        bombing();
      } else if (movie.currentFrameNumber() == movie.frameCount() - 1) {
        delete this;
        return;
      }
    } else {
      moveForward();
      QList<QGraphicsItem *> items = collidingItems();
      if (!items.empty()) {
        for (QGraphicsItem *item : items) {
          if (item->type() == Enemy::Type &&
              qgraphicsitem_cast<Enemy *>(item)->getIsDead() == false) {
            isBombing = true;
            bombArea = new QGraphicsEllipseItem(this);
            bombArea->setPen(Qt::NoPen);
            bombArea->setRect(-bombRadius, -bombRadius, bombRadius * 2,
                              bombRadius * 2);
            break;
          }
        }
      }
    }
  }
}

void Missile::moveForward() {
  if (atkTarget.isNull() == false && atkTarget->getIsDead() == false) {
    QLineF ln(pos(), atkTarget.data()->pos());
    atkAngle = -ln.angle();
  }

  setRotation(atkAngle);

  qreal dy = speed * qSin(qDegreesToRadians(atkAngle));
  qreal dx = speed * qCos(qDegreesToRadians(atkAngle));

  moveBy(dx, dy);
}

void Missile::bombing() {
  QList<QGraphicsItem *> items = bombArea->collidingItems();
  for (QGraphicsItem *item : items) {
    if (item->type() == Enemy::Type) {
      Enemy *e = qgraphicsitem_cast<Enemy *>(item);
      e->HP.changeCurValue(-atk);
      e->underAtk = true;
    }
  }
}

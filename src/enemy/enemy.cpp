// Copyright 2022 Flying-Tom

#include <enemy/enemy.h>

Enemy::Enemy(Game *game, QList<QPointF> *path, int money, GameValue<qreal> HP,
             GameValue<qreal> atk, GameValue<qreal> speed, int moveType,
             qreal atkRadius)
    : game(game), points(*path), dest(points[1]), pointIndex(1),
      moveType(moveType), isStopped(false), canAttackMelee(false),
      canAttackRange(false) {
  GameItem::HP = HP;
  GameItem::atkRadius = atkRadius;
  GameItem::isDead = false;
  GameItem::money = money;
  GameItem::atk = atk;
  GameItem::speed = speed;
  deathCounter = GameValue<int>(0, 100);

  atkArea->setRect(-atkRadius, -atkRadius, atkRadius * 2, atkRadius * 2);

  HPMeter->setBrush(QBrush(QColor(QColor(255, 38, 0))));

  setPos(GameMap::BlockToCoordinate(GameMap::CoordinateToBlock(points[0])));
}

Enemy::~Enemy() {
  game->statistic.enemyNum.changeCurValue(-1);
  if (atkTarget.isNull() == false && atkTarget->type() == Tower::Type) {
    atkTarget->blockNumber.changeCurValue(-1);
  }
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)

  GameItem::paint(painter, option, widget);
  if (isDead == true) {
    QFont font;
    HPMeter->hide();
    font.setPointSizeF(12);
    painter->setFont(font);
    painter->setPen(Qt::yellow);
    painter->drawImage(QRectF(-25, -15, 20, 20), QImage(":images/coin.png"));
    painter->drawText(0, 0, QString("+") + QString::number(money));
  } else {
    if (underAtk == true) {
      painter->setOpacity(0.5);
      if (blinkCounter.getCurValue() > 0) {
        blinkCounter.changeCurValue(-1);
      } else {
        blinkCounter.setCurValue(blinkCounter.getMaxValue());
        underAtk = false;
      }
    } else {
      painter->setOpacity(1);
    }

    if (x() <= dest.x()) {
      painter->drawImage(boundingRect(), movie.currentImage());
    } else {
      painter->drawImage(boundingRect(),
                         movie.currentImage().mirrored(true, false));
    }
    // painter->drawPath(shape());
  }

  if (atkTarget != nullptr && atkMovie.isValid()) {
    painter->drawImage(atkMovieRect, atkMovie.currentImage());
  }
}

void Enemy::moveForward() {
  qreal theta = 0;
  QLineF ln(pos(), dest);
  theta = -ln.angle();

  if (ln.length() < 2 * speed.getCurValue()) {
    if (pointIndex < points.length() - 1) {
      dest = points[++pointIndex];
      theta = -QLineF(pos(), dest).angle();
    } else {
      game->statistic.life.changeCurValue(-1);
      delete this;
      return;
    }
  }

  qreal dy = speed.getCurValue() * qSin(qDegreesToRadians(theta));
  qreal dx = speed.getCurValue() * qCos(qDegreesToRadians(theta));

  moveBy(dx, dy);
}

void Enemy::aquireTarget() {
  QList<QGraphicsItem *> colliding_items = atkArea->collidingItems();
  for (QGraphicsItem *item : colliding_items) {
    if (item->type() == Tower::Type) {
      Tower *t = qgraphicsitem_cast<Tower *>(item);
      if ((t->getAtkType() == Tower::RANGE && canAttackRange == false) ||
          (t->getAtkType() == Tower::MELEE && canAttackMelee == false) ||
          (t->blockNumber.getCurValue() >= t->blockNumber.getMaxValue())) {
        continue;
      } else {
        atkTarget = t;
        break;
      }
    }
  }

  if (atkTarget.isNull()) {
    isStopped = false;
  } else {
    atkTarget->blockNumber.changeCurValue(1);
    atkMovieRect.setRect(atkTarget->x() - x() - atkMovieRect.width() / 2,
                         atkTarget->y() - y() - atkMovieRect.height() / 2,
                         atkMovieRect.width(), atkMovieRect.height());
    isStopped = true;
  }
}

void Enemy::attack() {
  if (atkMovie.isValid() &&
      atkMovie.currentFrameNumber() == atkMovie.frameCount() - 1) {
    atkTarget->HP.changeCurValue(-atk.getCurValue());
    atkTarget->underAtk = true;
    atkMovie.jumpToNextFrame();
    if (atkTarget->HP.getCurValue() <= 0) {
      atkTarget->blockNumber.changeCurValue(-1);
      atkTarget = nullptr;
      isStopped = false;
    }
  }
}

bool Enemy::getIsStopped() const { return isStopped; }

void Enemy::setIsStopped(bool newIsStopped) { isStopped = newIsStopped; }

int Enemy::getMoveType() const { return moveType; }

QPointF Enemy::getPoint(int index) const { return points[index]; }

QPointF Enemy::getDest() const { return dest; }

int Enemy::getpointIndex() { return pointIndex; }

void Enemy::advance(int phase) {
  if (!phase) {
    if (HP.getCurValue() == 0) {
      isDead = true;
      speed.setCurValue(0);
      game->statistic.money.changeCurValue(money);

      if (deathCounter.getCurValue() < deathCounter.getMaxValue()) {
        deathCounter.changeCurValue(1);
      } else {
        delete this;
        return;
      }
      return;
    }

    if (atkTarget.isNull())
      aquireTarget();
    if (atkTarget.isNull() == false) {
      attack();
    }

    if (isStopped == true) {
    } else {
      moveForward();
    }
  } else {
    update();
  }
}

int Enemy::type() const { return Type; }

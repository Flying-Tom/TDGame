// Copyright 2022 Flying-Tom

#include <enemy/robotsoldier.h>

#include <tower/tower.h>

RobotSoldier::RobotSoldier(Game *game, QList<QPointF> *path)
    : Enemy(game, path, 50, GameValue<qreal>(3000, 3000),
            GameValue<qreal>(10, 10), GameValue<qreal>(0.25, 0.25),
            EnemyMoveType::WALKING, 200),
      atkSpeed(50) {
  movie.setFileName(":/images/robotsoldier.gif");
  movie.start();

  atkMovie.setFileName(":/images/robotsoldierattack.gif");
  atkMovie.setSpeed(atkSpeed);
  atkMovie.start();

  canAttackMelee = true;
  canAttackRange = true;
}

void RobotSoldier::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  if (isStopped == true && atkTarget.isNull() == false) {
    qreal theta = 0;
    QLineF ln(pos(), atkTarget->pos());
    theta = -ln.angle();

    painter->setOpacity(0.7);
    painter->rotate(theta);
    painter->drawImage(QRectF(-125, -125, 300, 200), atkMovie.currentImage());
    painter->setOpacity(1);
    painter->rotate(-theta);
  }

  //    Enemy::paint(painter, option, widget);
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

    if (x() < dest.x()) {
      painter->drawImage(boundingRect(), movie.currentImage());
    } else {
      painter->drawImage(boundingRect(),
                         movie.currentImage().mirrored(true, false));
    }
    // painter->drawPath(shape());

    HPMeter->setRect(-60, 40, (qreal)HP.getCurValue() / HP.getMaxValue() * 150,
                     12);
  }
}

QRectF RobotSoldier::boundingRect() const {
  return QRectF(-80, -120, 160, 160);
}

QPainterPath RobotSoldier::shape() const {
  QPainterPath path;
  path.addRect(QRectF(-50, -90, 128, 128));
  return path;
}

void RobotSoldier::attack() {
  atkTarget->HP.changeCurValue(-0.05 * (qreal)atkSpeed / 100.0);
  atkTarget->underAtk = true;
  Tower *t = Tower::castItem(atkTarget.data());
  if (t != nullptr && t->HP.getCurValue() <= 0) {
    isStopped = false;
    atkSpeed = 50;
  }

  atkSpeed = std::min(atkSpeed + 0.3, 400.0);
  atkMovie.setSpeed(atkSpeed);
}

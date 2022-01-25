#include <enemy/fallenwarrior.h>

FallenWarrior::FallenWarrior(Game* game, QList<QPointF>& path)
    : Enemy(game,
        path,
        30,
        GameValue<qreal>(200, 200),
        GameValue<qreal>(500, 500),
        GameValue<qreal>(2, 2),
        Enemy::WALKING,
        60)
{
    movie.setFileName(":/images/fallenwarrior.gif");
    movie.setCacheMode(QMovie::CacheAll);
    movie.start();

    canAttackMelee = true;
    canAttackRange = false;
}

QRectF FallenWarrior::boundingRect() const
{
    return QRectF(-75, -105, 300, 150);
}

QPainterPath FallenWarrior::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(-40, -40, 80, 80));
    return path;
}

void FallenWarrior::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
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

        if (x() < dest.x()) {
            painter->drawImage(QRectF(-75, -105, 300, 150), movie.currentImage());
        } else {
            painter->drawImage(QRectF(-240, -105, 300, 150),
                movie.currentImage().mirrored(true, false));
        }
        // painter->drawPath(shape());
    }

    if (atkTarget != nullptr and atkMovie.isValid()) {
        painter->drawImage(atkMovieRect, atkMovie.currentImage());
    }
}

void FallenWarrior::attack()
{
    if (movie.currentFrameNumber() == movie.frameCount() - 1) {
        atkTarget->HP.changeCurValue(-atk.getCurValue());
        atkTarget->underAtk = true;

        movie.jumpToFrame(5);
        if (atkTarget->HP.getCurValue() <= 0) {
            atkTarget->blockNumber.changeCurValue(-1);
            atkTarget = nullptr;
            isStopped = false;
        }
    }
}

void FallenWarrior::advance(int phase)
{
    if (!phase) {
        if (HP.getCurValue() == 0) {
            isDead = true;
            speed.setCurValue(0);

            if (deathCounter.getCurValue() < deathCounter.getMaxValue()) {
                deathCounter.changeCurValue(1);
            } else {
                game->statistic.money.changeCurValue(money);
                delete this;
                return;
            }
            return;
        }

        if (atkTarget.isNull())
            aquireTarget();
        if (atkTarget.isNull() == false) {
            attack();
        } else {
            if (movie.currentFrameNumber() > 4) {
                movie.jumpToFrame(1);
            }
        }

        if (isStopped == true) {
            ;
        } else {
            moveForward();
        }
    } else {
        update();
    }
}

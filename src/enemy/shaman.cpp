#include <enemy/shaman.h>

Shaman::Shaman(Game* game, QList<QPointF>& path)
    : Enemy(game,
        path,
        50,
        GameValue<qreal>(200, 200),
        GameValue<qreal>(100, 100),
        GameValue<qreal>(1, 100),
        Enemy::WALKING,
        150)
{
    movie.setFileName(":/images/shaman.gif");
    movie.start();

    atkMovie.setFileName(":/images/shamanattack.gif");
    atkMovie.start();
    atkMovieRect.setWidth(160);
    atkMovieRect.setHeight(160);

    canAttackMelee = true;
    canAttackRange = false;
}

void Shaman::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (atkTarget.isNull() == false) {
        atkMovieRect.setRect(atkTarget->x() - x() - atkMovieRect.width() / 2,
            atkTarget->y() - y() - atkMovieRect.height() / 2,
            160,
            160);
    }
    Enemy::paint(painter, option, widget);
}

QPainterPath Shaman::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Shaman::aquireTarget()
{
    QList<QGraphicsItem*> colliding_items = atkArea->collidingItems();
    foreach (QGraphicsItem* item, colliding_items) {
        if (item->type() == Enemy::Type) {
            if (((Enemy*)item)->HP.getMaxValue() == ((Enemy*)item)->HP.getCurValue())
                continue;
            else {
                atkTarget = (Enemy*)item;
                break;
            }
        }
    }

    if (atkTarget.isNull()) {
        isStopped = false;
    } else {
        // atkMoiveRect.setRect(atkTarget->x() - x() - atkMoiveRect.width() / 2,
        //     atkTarget->y() - y() - atkMoiveRect.height() / 2,
        //     atkMoiveRect.width(),
        //     atkMoiveRect.height());
        // isStopped = true;
        // qDebug() << "hasTarget";
    }
}

void Shaman::attack()
{
    if (atkTarget->getIsDead() == false
        and atkMovie.currentFrameNumber() == atkMovie.frameCount() - 1) {
        if (atkTarget != this) {
            speed.setCurValue(atkTarget->speed.getCurValue());
            isStopped = ((Enemy*)atkTarget.data())->getIsStopped();
        }
        atkTarget->HP.changeCurValue(atk.getCurValue());
        atkMovie.jumpToNextFrame();
        atkTarget.clear();
    }
}

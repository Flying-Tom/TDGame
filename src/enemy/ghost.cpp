#include <enemy/ghost.h>

Ghost::Ghost(Game* game, QList<QPointF>& path)
    : Enemy(game,
        path,
        50,
        GameValue<qreal>(500, 500),
        GameValue<qreal>(10, 10),
        GameValue<qreal>(1.5, 1.5),
        Enemy::WALKING,
        60)
{
    movie.setFileName(":/images/ghost.gif");
    movie.start();

    canAttackMelee = true;
    canAttackRange = false;
}

QPainterPath Ghost::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(-30, -30, 60, 60));
    return path;
}

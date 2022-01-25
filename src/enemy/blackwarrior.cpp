#include <enemy/blackwarrior.h>

BlackWarrior::BlackWarrior(Game* game, QList<QPointF>& path)
    : Enemy(game,
        path,
        30,
        GameValue<qreal>(100, 100),
        GameValue<qreal>(10, 10),
        GameValue<qreal>(2, 2),
        Enemy::WALKING,
        60)
{
    movie.setFileName(":/images/blackwarrior.gif");
    movie.start();

    canAttackMelee = true;
    canAttackRange = false;
}

QPainterPath BlackWarrior::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(-20, -25, 60, 60));
    return path;
}

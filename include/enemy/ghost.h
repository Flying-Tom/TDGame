#ifndef GHOST_H
#define GHOST_H

#include "enemy.h"

class Ghost : public Enemy {
public:
    Ghost(Game* game, QList<QPointF>& path);
    //    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;
};

#endif // GHOST_H

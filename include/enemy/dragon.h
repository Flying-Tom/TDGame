#ifndef DRAGON_H
#define DRAGON_H

#include "enemy.h"
#include "game.h"

class Dragon : public Enemy {
public:
    Dragon(Game* game, QList<QPointF>& path);
    ~Dragon();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
};

#endif // DRAGON_H

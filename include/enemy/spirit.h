#ifndef SPIRIT_H
#define SPIRIT_H

#include "enemy.h"

class Spirit : public Enemy {
public:
    Spirit(Game* game, QList<QPointF>& path);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
};

#endif // SPIRIT_H

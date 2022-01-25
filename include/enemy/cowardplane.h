#ifndef COWARDPLANE_H
#define COWARDPLANE_H

#include "enemy.h"
#include "game.h"

class CowardPlane : public Enemy {
public:
    CowardPlane(Game* game, QList<QPointF>& path);
    QPainterPath shape() const override;
    void advance(int phase) override;
};

#endif // COWARDPLANE_H

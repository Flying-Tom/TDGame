#ifndef BLACKWARRIOR_H
#define BLACKWARRIOR_H

#include "enemy.h"
#include "game.h"

class BlackWarrior : public Enemy {
public:
    BlackWarrior(Game* game, QList<QPointF>& path);
    QPainterPath shape() const override;
};

#endif // BLACKWARRIOR_H

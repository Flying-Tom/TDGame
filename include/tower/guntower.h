#ifndef GUNTOWER_H
#define GUNTOWER_H

#include "tower.h"
#include <bullet/gunbullet.h>

class GunTower : public Tower {
public:
    GunTower(Map* map);
    ~GunTower();
    QRectF boundingRect() const override;

public:
    void attack() override;
};

#endif // GUNTOWER_H

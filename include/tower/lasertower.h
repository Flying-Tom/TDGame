#ifndef LASERTOWER_H
#define LASERTOWER_H

#include "tower.h"
#include <bullet/laser.h>

class LaserTower : public Tower {
public:
    LaserTower(Map* map);
    ~LaserTower();
    QRectF boundingRect() const override;

    void attack() override;

    Laser* getTrajectory() const;
    void setTrajectory(Laser* newTrajectory);

protected:
    int prevAngle;
    Laser* trajectory;

public:
    void aquireTarget() override;
};

#endif // LASERTOWER_H

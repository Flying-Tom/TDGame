#ifndef MISSILETOWER_H
#define MISSILETOWER_H

#include "tower.h"
#include <bullet/missile.h>

class MissileTower : public Tower {
public:
    MissileTower(Map* map);
    ~MissileTower();

    void aquireTarget() override;
    void attack() override;
};

#endif // MISSILETOWER_H

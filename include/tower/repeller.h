#ifndef REPELLER_H
#define REPELLER_H

#include "tower.h"

class Repeller : public Tower {
public:
    Repeller(Map* map);
    ~Repeller();
    void advance(int phase) override;
};

#endif // REPELLER_H

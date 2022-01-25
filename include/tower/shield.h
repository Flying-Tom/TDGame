#ifndef SHIELD_H
#define SHIELD_H

#include "tower.h"

class Shield : public Tower {
public:
    Shield(Map* map);
    ~Shield();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;
};

#endif // SHIELD_H

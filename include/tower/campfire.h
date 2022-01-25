#ifndef CAMPFIRE_H
#define CAMPFIRE_H

#include "tower.h"
class CampFire : public Tower {
public:
    CampFire(Map* map);
    ~CampFire();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    int angle;
    void aquireTarget() override;
    void advance(int phase) override;

    QMovie movie;
};

#endif // CAMPFIRE_H

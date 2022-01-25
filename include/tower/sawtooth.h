#ifndef SAWTOOTH_H
#define SAWTOOTH_H

#include "tower.h"

class SawTooth : public Tower {
public:
    SawTooth(Map* map);
    ~SawTooth();
    void advance(int phase) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    int angle;
};

#endif // SAWTOOTH_H

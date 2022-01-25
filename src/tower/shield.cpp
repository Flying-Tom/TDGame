#include <tower/shield.h>

Shield::Shield(Map* map)
    : Tower(map,
        "shield",
        GameValue<qreal>(100, 100),
        RANGE,
        200,
        GameValue<int>(0, 5),
        GameValue<int>(0, 175))
{
    image = QImage(":images/shield.png");
    HPMeter->setBrush(QBrush(Qt::yellow));
    setZValue(5);
}

Shield::~Shield() { }

void Shield::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Tower::paint(painter, option, widget);
    painter->setBrush(QColor(0, 204, 255));
    painter->setOpacity(0.1);
    painter->drawEllipse(atkArea->boundingRect());
    //atkArea->show();
}

void Shield::advance(int phase)
{
    if (!phase) {
        if (HP.getCurValue() == 0) {
            delete this;
            return;
        }

        foreach (QGraphicsItem* item, atkArea->collidingItems()) {
            if (item->type() == Tower::Type and ((Tower*)item)->getAtkType() == Tower::RANGE
                and item != this) {
                if (((Tower*)item)->getName() != "shield"
                    and ((Tower*)item)->HP.getCurValue() > 0) {
                    double delta = ((Tower*)item)->HP.getMaxValue()
                        - ((Tower*)item)->HP.getCurValue();
                    ((Tower*)item)->HP.changeCurValue(delta);
                    HP.changeCurValue(-delta);
                }
            }
        }
    }
}

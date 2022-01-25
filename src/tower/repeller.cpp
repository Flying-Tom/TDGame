#include <tower/repeller.h>

Repeller::Repeller(Map* map)
    : Tower(map, "repeller", GameValue<qreal>(6000, 6000), MELEE, 50, GameValue<int>(0, 3))
{
    image = QImage(":images/repeller.png");
}

Repeller::~Repeller() { }

void Repeller::advance(int phase)
{
    if (!phase) {
        if (HP.getCurValue() == 0) {
            delete this;
            return;
        }
        //        QList<QGraphicsItem *> items = collidingItems();
        //        if (!items.empty()) {
        //            foreach (QGraphicsItem *item, items) {
        //                if (item->type() == Enemy::Type) {
        //                    Enemy *e = qgraphicsitem_cast<Enemy *>(item);
        //                    //                    if (e->getIsDead() == false) {
        //                    //                        QLineF ln(e->pos(), e->getPoint(e->getpointIndex() - 1));

        //                    //                        qreal length = (qreal) QRandomGenerator::global()->bounded(5, 8) / 10
        //                    //                                       * ln.length();

        //                    //                        qreal dy = length * qSin(qDegreesToRadians(-ln.angle()));
        //                    //                        qreal dx = length * qCos(qDegreesToRadians(-ln.angle()));

        //                    //                        e->setPos(e->pos().x() + dx, e->pos().y() + dy);
        //                    //                        //e->changeHP(-0.5);
        //                    //                        HP -= 1;
        //                    //                    }
        //                }
        //            }
        //        }
    } else {
        update();
    }
}

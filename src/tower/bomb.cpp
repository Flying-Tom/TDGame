#include <tower/bomb.h>

Bomb::Bomb(Map* map)
    : Tower(map, "bomb", GameValue<qreal>(8, 8), MELEE, 256, GameValue<int>(0, 20))
    , movie(":images/bomb.gif")
{
    image = QImage(":images/bomb.png");
}

Bomb::~Bomb() { }

void Bomb::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    //    Tower::paint(painter, option, widget);
    GameItem::paint(painter, option, widget);
    if (HP.getCurValue() == 0) {
        painter->drawImage(QRectF(-256, -256, 512, 512), movie.currentImage());
    } else {
        painter->drawImage(boundingRect(), image);
    }
}

void Bomb::advance(int phase)
{
    if (!phase) {
        if (HP.getCurValue() == 0) {
            if (movie.state() == QMovie::NotRunning) {
                movie.start();
                bombing();
            } else if (movie.currentFrameNumber() >= movie.frameCount() - 2) {
                delete this;
                return;
            }
        }
    } else {
        update();
    }
}

void Bomb::bombing()
{
    QList<QGraphicsItem*> colliding_items = atkArea->collidingItems();
    if (!colliding_items.empty()) {
        foreach (QGraphicsItem* item, colliding_items) {
            if (item->type() == Enemy::Type) {
                Enemy* e = qgraphicsitem_cast<Enemy*>(item);
                if (e->getMoveType() == Enemy::WALKING)
                    e->HP.setCurValue(0);
            } else if (item->type() == Tower::Type) {
                GameItem* gi = (GameItem*)item;
                if (gi->getName() == QString("bomb") or gi->getName() == QString("repeller")) {
                    gi->HP.setCurValue(0);
                }
            }
        }
    }
}

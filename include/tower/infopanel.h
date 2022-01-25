#ifndef INFOPANEL_H
#define INFOPANEL_H

#include <common.h>
#include <gameitem.h>

class InfoPanel : public QGraphicsItem {
    Q_INTERFACES(QGraphicsItem)
public:
    InfoPanel(GameItem* parent = 0);
    ~InfoPanel();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    GameItem* parent;
};

#endif // INFOPANEL_H

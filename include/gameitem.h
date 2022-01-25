#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <common.h>

class GameItem : public QGraphicsObject {
public:
    GameItem();
    virtual ~GameItem();

public:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    virtual void aquireTarget() = 0;
    virtual void attack() = 0;

    virtual bool getIsDead() const;
    virtual void setIsDead(bool newIsDead);

    QPointer<GameItem> getAtkTarget() const;
    void setAtkTarget(QPointer<GameItem> newAtkTarget);

    const QString& getName() const;
    void setName(const QString& newName);

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

protected:
    QString name;

    int money;
    qreal atkRadius;
    bool isDead;

    QPointer<GameItem> atkTarget;

public:
    GameValue<qreal> HP;
    GameValue<qreal> atk;
    GameValue<qreal> speed;
    GameValue<int> blockNumber;
    GameValue<int> aquireCounter;
    QGraphicsEllipseItem* atkArea;
    QGraphicsRectItem* HPMeter;
    bool underAtk;
    GameValue<int> blinkCounter;
};

#endif // GAMEITEM_H

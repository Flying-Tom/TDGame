#include <gameitem.h>

GameItem::GameItem()
{
    atkTarget = nullptr;
    atkArea = new QGraphicsEllipseItem(this);
    QPen pen = atkArea->pen();
    pen.setWidth(3);
    pen.setColor(QColor(255, 255, 255));
    pen.setStyle(Qt::DotLine);
    atkArea->setPen(pen);
    atkArea->hide();
    HPMeter = new QGraphicsRectItem(this);
    HPMeter->setPen(Qt::NoPen);
    underAtk = false;
    blinkCounter = GameValue<int>(10, 10);
}

GameItem::~GameItem()
{
    delete atkArea;
    delete HPMeter;
}

QRectF GameItem::boundingRect() const
{
    return QRectF(-40, -40, 80, 80);
}

void GameItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if (HP.getCurValue() == 0) {
        HPMeter->hide();
    } else {
        HPMeter->setRect(-30, 40, (qreal)HP.getCurValue() / HP.getMaxValue() * 60, 8);
    }
}

bool GameItem::getIsDead() const
{
    return isDead;
}

void GameItem::setIsDead(bool newIsDead)
{
    isDead = newIsDead;
}

QPointer<GameItem> GameItem::getAtkTarget() const
{
    return atkTarget;
}

void GameItem::setAtkTarget(QPointer<GameItem> newAtkTarget)
{
    atkTarget = newAtkTarget;
}

const QString& GameItem::getName() const
{
    return name;
}

void GameItem::setName(const QString& newName)
{
    name = newName;
}

void GameItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    atkArea->show();
}

void GameItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    atkArea->hide();
}

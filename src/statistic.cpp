#include <enemy/enemy.h>
#include <game.h>
#include <shop.h>
#include <statistic.h>

int Statistic::frameCount = 0;

Statistic::Statistic(Game* game)
    : game(game)
    , shopBackground(":images/shop.png")
    , lifeIcon(":images/life.png")
    , coinIcon(":images/coin.png")
{
    setAcceptDrops(false);
    life = GameValue<int>(20, 50);
    money = GameValue<int>(1000000, 1000000);
    moneyAddCounter = GameValue<int>(500, 500);
    FPS = 0;

    Shop* icon = nullptr;

    icon = new Shop(Shop::name[0], 0, 0, 64, 128);
    icon->setParentItem(this);
    icon->setPos(1290, 55 + 96 * 1);

    icon = new Shop(Shop::name[3], 0, 0, 64, 128);
    icon->setParentItem(this);
    icon->setPos(1450, 55 + 96 * 1);

    icon = new Shop(Shop::name[1], 0, 0, 64, 64);
    icon->setParentItem(this);
    icon->setPos(1290, 85 + 96 * 2);

    icon = new Shop(Shop::name[2], 0, 0, 64, 64);
    icon->setParentItem(this);
    icon->setPos(1450, 85 + 96 * 2);

    icon = new Shop(Shop::name[4], 0, 0, 64, 64);
    icon->setParentItem(this);
    icon->setPos(1450, 85 + 96 * 3);

    icon = new Shop(Shop::name[5], 0, 0, 64, 64);
    icon->setParentItem(this);
    icon->setPos(1450, 85 + 96 * 4);

    icon = new Shop(Shop::name[6], 0, 0, 64, 64);
    icon->setParentItem(this);
    icon->setPos(1450, 85 + 96 * 5);

    icon = new Shop(Shop::name[7], 0, 0, 64, 64);
    icon->setParentItem(this);
    icon->setPos(1290, 85 + 96 * 3);
}

QRectF Statistic::boundingRect() const
{
    return QRectF(1280, 0, 320, 1000);
}

void Statistic::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(QColor(78, 85, 97));
    painter->drawRect(boundingRect());

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(62, 69, 80));
    painter->drawRect(QRectF(1290, 140, 300, 800));

    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->setPen(Qt::white);

    painter->drawImage(QRectF(1380, 45, 25, 25), lifeIcon);
    painter->drawText(QRectF(1420, 40, 100, 50), QString::number(life.getCurValue()));
    painter->drawImage(QRectF(1380, 73, 30, 30), coinIcon);
    painter->drawText(QRectF(1420, 70, 100, 50), QString::number(money.getCurValue()));

    font.setPointSizeF(9);
    painter->setFont(font);
    painter->setPen(Qt::gray);
    painter->drawText(QRectF(1540, 5, 100, 50), QString("%1").arg(FPS, -3) + QString(" FPS"));

    painter->drawText(QRectF(1500, 880, 100, 50),
        QString("%1").arg(Enemy::enemyCount, -3) + QString(" enemies"));
    painter->drawText(QRectF(1500, 900, 100, 50),
        QString("%1").arg(scene()->items().size(), -3) + QString(" items"));

    if (game->FPSCounterTimer.hasExpired(1000)) {
        FPS = frameCount;
        frameCount = 0;
        game->FPSCounterTimer.restart();
    }
}

void Statistic::advance(int phase)
{
    if (!phase) {
        if (life.getCurValue() == 0) {
            game->endThisGame("GameOver");
        }

        if (FPS < 75) {
            if (game->spawnTimer.isActive() == true) {
                game->spawnTimer.stop();
            }
        } else {
            if (game->spawnTimer.isActive() == false) {
                game->spawnTimer.start(2000 / game->gameSpeed);
            }
        }

        if (moneyAddCounter.getCurValue() < moneyAddCounter.getMaxValue()) {
            moneyAddCounter.changeCurValue(1);
        } else {
            moneyAddCounter.setCurValue(0);
            money.changeCurValue(200);
        }

    } else {
        ++frameCount;
        update();
    }
}

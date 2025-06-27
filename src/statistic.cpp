// Copyright 2022 Flying-Tom

#include <enemy/enemy.h>
#include <game.h>
#include <shop.h>
#include <statistic.h>

int Statistic::frameCount = 0;

Statistic::Statistic(Game *game)
    : game(game), shopBackground(":images/shop.png"),
      lifeIcon(":images/life.png"), coinIcon(":images/coin.png") {
  setAcceptDrops(false);
  life = GameValue<int>(20, 50);
  money = GameValue<int>(1000000, 1000000);
  moneyAddCounter = GameValue<int>(500, 500);
  FPS = 0;

  int shopXoffset = 1300, shopYoffset = 160;
  int shopItemInterval = 96;
  for (int i = 0; i < 8; i++) {
    Shop *icon = nullptr;
    int shopItemX = 64, shopItemY = 64;
    if (i == 0 || i == 1) {
      // no square icon
      shopItemX = 64;
      shopItemY = 128;
    } else if (i == 2) {
      // extra offset
      shopYoffset += 20;
    }
    icon = new Shop(Shop::name[i], 0, 0, shopItemX, shopItemY);
    icon->setParentItem(this);
    icon->setPos(shopXoffset, shopYoffset + shopItemInterval * i);
  }
}

QRectF Statistic::boundingRect() const { return QRectF(1280, 0, 320, 1000); }

void Statistic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)

  painter->setBrush(QColor(78, 85, 97));
  painter->drawRect(boundingRect());

  painter->setPen(Qt::NoPen);
  painter->setBrush(QColor(62, 69, 80));
  painter->drawRect(QRectF(1290, 140, 140, 800));

  QFont font;
  font.setPointSizeF(15);
  painter->setFont(font);
  painter->setPen(Qt::white);

  painter->drawImage(QRectF(1300, 45, 25, 25), lifeIcon);
  painter->drawText(QRectF(1340, 40, 100, 50),
                    QString::number(life.getCurValue()));
  painter->drawImage(QRectF(1300, 73, 30, 30), coinIcon);
  painter->drawText(QRectF(1340, 70, 100, 50),
                    QString::number(money.getCurValue()));

  font.setPointSizeF(9);
  painter->setFont(font);
  painter->setPen(Qt::gray);
  painter->drawText(QRectF(1200, 10, 100, 50), QString("%1 FPS").arg(FPS, -3));

  painter->drawText(QRectF(1200, 30, 100, 50),
                    QString("%1 enemies").arg(enemyNum.getCurValue(), -3));
  painter->drawText(QRectF(1200, 50, 100, 50),
                    QString("%1 items").arg(scene()->items().size(), -3));

  if (game->FPSCounterTimer.hasExpired(1000)) {
    FPS = frameCount;
    frameCount = 0;
    game->FPSCounterTimer.restart();
  }
}

void Statistic::advance(int phase) {
  if (!phase) {
    if (life.getCurValue() == 0) {
      game->endThisGame("GameOver");
    }

    // self-adaptive spawn speed (performance optimization)
    if (FPS < 30 || enemyNum.getCurValue() >= enemyNum.getMaxValue()) {
      game->stopSpawn();
    } else {
      game->startSpawn(false);
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

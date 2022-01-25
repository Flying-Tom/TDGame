#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <common.h>
#include <game.h>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* e) override;

    Game* getGame() const;
    void setGame(Game* newGame);
    QString mapConfig;

    //    void loadStyleSheet(const QString &styleSheetFile);

public slots:
    void startGame();
    void chooseMap();
    void exportMap();

private:
    Game* game;
    int starticonangle;
};

#endif // MAINWINDOW_H

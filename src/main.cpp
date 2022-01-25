#include <QApplication>
#include <game.h>
#include <mainwindow.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowIcon(QIcon(":/images/icon.png"));
    w.setWindowTitle("Tom's TD Game");
    w.show();

    return a.exec();
}

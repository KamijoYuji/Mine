#include <QCoreApplication>
#include <QtWidgets>
#include "window.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,w.size(),qApp->desktop()->availableGeometry()));
    w.setFixedSize(250,300);
    w.setStyleSheet("background-color: black; color: white");
    w.setWindowTitle("Minesweeper");
    QPixmap i("b.png");
    QIcon m(i);
    w.setWindowIcon(m);
    w.show();
    return a.exec();
}

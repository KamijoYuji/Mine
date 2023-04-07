#ifndef SBUTTON_H
#define SBUTTON_H
#include "custombutton.h"
#include <QObject>
#include <QtWidgets>
#include <QSizePolicy>
#include <QTreeView>


class sbutton : public QLabel
{
    Q_OBJECT
public:
    sbutton(int x, int y, int ar, QWidget* pwgt=0);
    customButton* pb;
    int mx;
    int my;
    int ar1;
    int ar2;
    int setNumber();
signals:
    void signalWin();
    void signalBoom();
    void signalNoBoom1();
    void signalNoBoom2();
    void signalNoBoom3();
    void signalHB();
    void signalO();
    void signalOver();
public slots:
    void slotWin();
    void slotButtonClicked();
    void slotButtonNoBomb();
    void slotButtonBomb();
};

#endif // SBUTTON_H

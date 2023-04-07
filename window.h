#ifndef WINDOW_H
#define WINDOW_H
#include <QtWidgets>
#include "sbutton.h"
#include <QFile>

class Window : public QWidget
{
    Q_OBJECT
public:
    Window(QWidget *parent = 0);
    ~Window();
    QTimer *tmr = new QTimer();
    int ct;
    int bombs[4];
    int sizex[4];
    int sizey[4];
    int flag[4];
    QPushButton* r = new QPushButton();
    QPushButton* exit = new QPushButton();
    QPushButton* lvl = new QPushButton();
    QLCDNumber* timer_q = new QLCDNumber(3);
    QLCDNumber* counter_q = new QLCDNumber(3);

    QMenu* r_m = new QMenu("Exit");
    QMenu* lvl_m = new QMenu("Diff");
    QMenu* help_m = new QMenu("Help");
private:
    QGridLayout *grid;
public slots:
    void slotInfo();
    void slotHelp();
    void slot1Diff();
    void slot2Diff();
    void slot3Diff();
    void slot4Diff();
    void slotSuperLvl();
    void slotBDiff();
    void slotGen();
    void slotBR2();
    void slotProverka();
    void slotUpdateTime();
    void slotClose();
    void slotGameOver();
    void slotWin();
    void slotCount1();
    void slotCount2();
    void slotCount3();
};

#endif // WINDOW_H

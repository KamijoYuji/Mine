#include "window.h"
#include <QGridLayout>
#include <QLCDNumber>
int bbbbbb = 0;
int h = 0;
int xx = 0;
int yy = 0;
int er = 0;
int lol = 0;
int re = 0;
int diff = 0;
int diff2 = 0;
bool booldiff = 0;
int xxxx = 5;
int yyyy = 1;
int bbbbb = 3;
int lll = 0;
bool sprlvl = 0;
int win = 0;
int lose = 0;
Window::Window(QWidget *parent): QWidget(parent)
{

    bombs[0] = 10;
    sizex[0] = 9;
    sizey[0] = 9;
    flag[0]=bombs[0];

    bombs[1] = 35;
    sizex[1] = 16;
    sizey[1] = 16;
    flag[1]=bombs[1];

    bombs[2] = 99;
    sizex[2] = 16;
    sizey[2] = 30;
    flag[2]=bombs[2];

    bombs[3] = 3;
    sizex[3] = 5;
    sizey[3] = 1;
    flag[3] = bombs[3];

    grid = new QGridLayout(this);
    grid->setSpacing(0);

    timer_q->setFixedSize(25,25);
    timer_q->setStyleSheet("background-color: grey; color: white");
    timer_q->display(0);
    grid->addWidget(timer_q,1000,2);

    counter_q->display(flag[diff]);
    counter_q->setFixedSize(25,25);
    counter_q->setStyleSheet("background-color: grey; color: white");
    grid->addWidget(counter_q,1000,1);


    slotGen();

    exit->setFixedSize(25,25);

    exit->setText("Exit");
    exit->setStyleSheet("background-color: red; color: white");
    connect(exit,&QPushButton::clicked,this,&Window::slotClose);
    grid->addWidget(exit,1000,0);


    r->setFixedSize(25,25);
    QPixmap m ("game.png");
    QIcon ii(m);
    r->setIcon(ii);
    r->setIconSize(m.rect().size());
    connect(r,&QPushButton::clicked,this,&Window::slotBR2);
    grid->addWidget(r,1000,3);

    QPixmap q0 ("lvl1.png");
    QPixmap q1 ("lvl2.png");
    QPixmap q2 ("lvl3.png");
    QPixmap q3 ("lvl4.png");
    QIcon i1(q0);
    QIcon i2(q1);
    QIcon i3(q2);
    QIcon i4(q3);
    lvl->setIconSize(q0.rect().size());
    lvl->setFixedSize(25,25);
    switch (diff) {
    case 0:
        lvl->setIcon(i1);
        break;
    case 1:
        lvl->setIcon(i2);
        break;
    case 2:
        lvl->setIcon(i3);
        break;
    case 3:
        lvl->setIcon(i4);
        break;
    }
    connect(lvl,&QPushButton::clicked,this,&Window::slotBDiff);
    grid->addWidget(lvl,1000,4);

    QMenuBar* bar = new QMenuBar;
    bar->addMenu(r_m);
    bar->addMenu(lvl_m);
    bar->addMenu(help_m);
    r_m->addAction("выход",this,SLOT(slotClose()),Qt::CTRL+Qt::Key_Q);
    lvl_m->addAction("сложность: новичок",this,SLOT(slot1Diff()),Qt::CTRL+Qt::Key_1);
    lvl_m->addAction("сложность: продвинутый",this,SLOT(slot2Diff()),Qt::CTRL+Qt::Key_2);
    lvl_m->addAction("сложность: профессионал",this,SLOT(slot3Diff()),Qt::CTRL+Qt::Key_3);
    lvl_m->addAction("сложность: кастомная",this,SLOT(slot4Diff()),Qt::CTRL+Qt::Key_4);
    r_m->addAction("рестарт",this,SLOT(slotBR2()),Qt::CTRL+Qt::Key_R);
    help_m->addAction("помощь",this,SLOT(slotHelp()),Qt::CTRL+Qt::Key_H);
    help_m->addAction("информация",this,SLOT(slotInfo()),Qt::CTRL+Qt::Key_I);
    help_m->setStyleSheet("color: blue");
    lvl_m->setStyleSheet("color: green");
    r_m->setStyleSheet("color: red");
    grid->setMenuBar(bar);

    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(slotUpdateTime()));
    ct = 0;
    setLayout(grid);
}

void Window::slotSuperLvl()
{
    QMessageBox* q = new QMessageBox(this);
    q->setWindowTitle("Custom Lvl");
    q->show();
    q->setStyleSheet("color: white");
    q->setText("Выберите размеры поля и кол-во бомб: X="+QString::number(xxxx)+"; Y="+QString::number(yyyy)+"; N="+QString::number(bbbbb));
    QAbstractButton* xxx1 = new QPushButton("x+");
    QAbstractButton* xxx2 = new QPushButton("x-");
    QAbstractButton* yyy1 = new QPushButton("y+");
    QAbstractButton* yyy2 = new QPushButton("y-");
    QAbstractButton* bbb1 = new QPushButton("bombs+");
    QAbstractButton* bbb2 = new QPushButton("bombs-");
    xxx1->setStyleSheet("background-color: white; color: blue");
    yyy1->setStyleSheet("background-color: white; color: red");
    bbb1->setStyleSheet("background-color: white; color: green");
    xxx2->setStyleSheet("background-color: white; color: blue");
    yyy2->setStyleSheet("background-color: white; color: red");
    bbb2->setStyleSheet("background-color: white; color: green");
    q->addButton(xxx1,QMessageBox::NoRole);
    q->addButton(xxx2,QMessageBox::NoRole);
    q->addButton(yyy1,QMessageBox::NoRole);
    q->addButton(yyy2,QMessageBox::NoRole);
    q->addButton(bbb1,QMessageBox::NoRole);
    q->addButton(bbb2,QMessageBox::NoRole);
    q->setStandardButtons(QMessageBox::Ok);
    int ret = q->exec();
    switch (ret) {
    case 0:
        xxxx++;
        q->setText("Выберите размеры поля и кол-во бомб: x="+QString::number(xxxx)+"; y="+QString::number(yyyy)+"; bombs="+QString::number(bbbbb));
        slotSuperLvl();
        break;
    case 1:
        xxxx--;
        q->setText("Выберите размеры поля и кол-во бомб: x="+QString::number(xxxx)+"; y="+QString::number(yyyy)+"; bombs="+QString::number(bbbbb));
        slotSuperLvl();
        break;
    case 2:
        yyyy++;
        q->setText("Выберите размеры поля и кол-во бомб: x="+QString::number(xxxx)+"; y="+QString::number(yyyy)+"; bombs="+QString::number(bbbbb));
        slotSuperLvl();
        break;
    case 3:
        yyyy--;
        q->setText("Выберите размеры поля и кол-во бомб: x="+QString::number(xxxx)+"; y="+QString::number(yyyy)+"; bombs="+QString::number(bbbbb));
        slotSuperLvl();
        break;
    case 4:
        bbbbb++;
        q->setText("Выберите размеры поля и кол-во бомб: x="+QString::number(xxxx)+"; y="+QString::number(yyyy)+"; bombs="+QString::number(bbbbb));
        slotSuperLvl();
        break;
    case 5:
        bbbbb--;
        q->setText("Выберите размеры поля и кол-во бомб: x="+QString::number(xxxx)+"; y="+QString::number(yyyy)+"; bombs="+QString::number(bbbbb));
        slotSuperLvl();
        break;
    case QMessageBox::Ok:
        if(xxxx*yyyy<=bbbbb or xxxx<=4 or yyyy<=0 or bbbbb<=0)
        {
            slotSuperLvl();
        }
        break;
    }


}
void Window::slot1Diff()
{
    booldiff=true;
    diff=0;
    QPixmap q0 ("lvl1.png");
    QIcon i1(q0);
    lvl->setIcon(i1);
    sprlvl = false;
    slotBR2();
}

void Window::slot2Diff()
{
    booldiff=true;
    diff=1;
    QPixmap q0 ("lvl2.png");
    QIcon i2(q0);
    lvl->setIcon(i2);
    sprlvl = false;
    slotBR2();
}

void Window::slot3Diff()
{
    booldiff=true;
    diff=2;
    QPixmap q0 ("lvl3.png");
    QIcon i3(q0);
    lvl->setIcon(i3);
    sprlvl = false;
    slotBR2();
}

void Window::slot4Diff()
{
    booldiff=true;
    diff=3;
    QPixmap q0 ("lvl4.png");
    QIcon i4(q0);
    lvl->setIcon(i4);
    sprlvl = true;
    slotSuperLvl();
    slotBR2();
}

void Window::slotBDiff()
{
    booldiff=true;
    diff++;
    if(diff==4)
    {
        diff=0;
    }
    QPixmap q0 ("lvl1.png");
    QPixmap q1 ("lvl2.png");
    QPixmap q2 ("lvl3.png");
    QPixmap q3 ("lvl4.png");
    QIcon i1(q0);
    QIcon i2(q1);
    QIcon i3(q2);
    QIcon i4(q3);
    switch (diff) {
    case 0:
        lvl->setIcon(i1);
        sprlvl = false;
        this->setFixedSize(250,300);
        break;
    case 1:
        lvl->setIcon(i2);
        sprlvl = false;
        this->setFixedSize(425,475);
        break;
    case 2:
        lvl->setIcon(i3);
        sprlvl = false;
        this->setFixedSize(775,475);
        break;
    case 3:
        lvl->setIcon(i4);
        sprlvl = true;
        slotSuperLvl();
        this->setFixedSize((sizey[diff]+1)*25,(sizex[diff]+3)*25);
        break;
    }
    slotBR2();
}

void Window::slotGen()
{
    lol = 0;
    h = 0;
    bool VT[sizex[diff]][sizey[diff]];
    srand(time(NULL));
    for(int i=0;i<sizex[diff];i++)
    {
        for(int j = 0;j<sizey[diff];j++)
        {
            VT[i][j] = 0;
        }
    }

    for(int i=bombs[diff];i>0;)
    {
        int k = rand()%sizex[diff];
        int d = rand()%sizey[diff];
        if(VT[k][d]==0)
        {
            VT[k][d] = 1;
            i--;
        }
    }


    int TAB [sizex[diff]+2][sizey[diff]+2];
    for(int i=0;i<sizex[diff]+2;i++)
    {
        for(int j = 0;j<sizey[diff]+2;j++)
        {
            TAB[i][j] = 0;
        }
    }

    for(int i=1;i<sizex[diff]+1;i++)
    {
        for(int j = 1;j<sizey[diff]+1;j++)
        {
            TAB[i][j] = VT[i-1][j-1];
        }
    }

    int VT_2[sizex[diff]][sizey[diff]];

    for(int i=0;i<sizex[diff];i++)
    {
        for(int j = 0;j<sizey[diff];j++)
        {
            if(TAB[i+1][j+1]==1)
            {
                VT_2[i][j] = 9;
            }
            else
            {
                VT_2[i][j] = TAB[i+1+1][j+1+1] + TAB[i+1][j+1+1] + TAB[i+1+1][j+1] + TAB[i+1-1][j+1] + TAB[i+1][j+1-1] + TAB[i+1-1][j+1+1] + TAB[i+1+1][j+1-1] + TAB[i+1-1][j+1-1];

            }
        }
    }

    for (int i=0; i<sizex[diff]; i++) {
        for (int j=0; j<sizey[diff]; j++) {
            sbutton* btn = new sbutton(i,j,VT_2[i][j]);
            btn->setFixedSize(25, 25);
            grid->addWidget(btn, i, j);
            btn->setStyleSheet("background-color: white");
            connect(btn, &sbutton::signalNoBoom1, this, &Window::slotCount1);
            connect(btn, &sbutton::signalNoBoom2, this, &Window::slotCount2);
            connect(btn, &sbutton::signalNoBoom3, this, &Window::slotCount3);
            connect(btn, &sbutton::signalO, this, &Window::slotProverka);
            connect(btn, &sbutton::signalBoom, this, &Window::slotGameOver);
        }
    }

}


void Window::slotBR2()
{
    win = 0;
    lose = 0;
    QLayoutItem* item[sizex[diff2]][sizey[diff2]];
    sbutton* btn_r[sizex[diff2]][sizey[diff2]];
    flag[diff2]=bombs[diff2];
    for(int i = 0; i<sizex[diff2]; i++){for(int j = 0; j<sizey[diff2]; j++){
            item[i][j] = grid->itemAtPosition(i,j);
            btn_r[i][j] = qobject_cast<sbutton*>(item[i][j]->widget());
            delete btn_r[i][j];
        }
    }
    ct=0;
    tmr->stop();
    QPixmap m ("game.png");
    QIcon ii(m);
    r->setIcon(ii);
    sizey[3]=xxxx;
    sizex[3]=yyyy;
    bombs[3]=bbbbb;
    flag[3]=bombs[3];
    this->setFixedSize((sizey[diff]+1)*25,(sizex[diff]+3)*25);
    timer_q->display(ct);
    counter_q->display(flag[diff]);
    diff2=diff;
    slotGen();
}

void Window::slotProverka()
{
    if (h == 0)
    {
        tmr->start();
        h++;
    }

    auto senderBtn = QObject::sender();
    sbutton* btn;
    btn = qobject_cast<sbutton*>(senderBtn);

    QLayoutItem* item[8];
    sbutton* btn_r[8];

    item[0] = grid->itemAtPosition(btn->mx+1,btn->my);
    if(btn->mx+1<sizex[diff]){btn_r[0] = qobject_cast<sbutton*>(item[0]->widget());
        if(btn_r[0]->ar1 ==0)
        {
            btn_r[0]->ar1=10;
            btn_r[0]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        } else if(btn_r[0]->ar1 <9 and btn_r[0]->ar1 >=0)
        {
            btn_r[0]->ar1=10;
            btn_r[0]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        }
    }

    item[1] = grid->itemAtPosition(btn->mx-1,btn->my);
    if(btn->mx-1>=0){btn_r[1] = qobject_cast<sbutton*>(item[1]->widget());
        if(btn_r[1]->ar1 ==0)
        {
            btn_r[1]->ar1=10;
            btn_r[1]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        } else if(btn_r[1]->ar1 <9 and btn_r[1]->ar1 >=0)
        {
            btn_r[1]->ar1=10;
            btn_r[1]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        }
    }

    item[2] = grid->itemAtPosition(btn->mx,btn->my+1);
    if(btn->my+1<sizey[diff]){btn_r[2] = qobject_cast<sbutton*>(item[2]->widget());
        if(btn_r[2]->ar1 ==0)
        {
            btn_r[2]->ar1=10;
            btn_r[2]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        } else if(btn_r[2]->ar1 <9 and btn_r[2]->ar1 >=0)
        {
            btn_r[2]->ar1=10;
            btn_r[2]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        }
    }

    item[3] = grid->itemAtPosition(btn->mx,btn->my-1);
    if(btn->my-1>=0){btn_r[3] = qobject_cast<sbutton*>(item[3]->widget());
        if(btn_r[3]->ar1 ==0)
        {
            btn_r[3]->ar1=10;
            btn_r[3]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        } else if(btn_r[3]->ar1 <9 and btn_r[3]->ar1 >=0)
        {
            btn_r[3]->ar1=10;
            btn_r[3]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        }
    }

    item[4] = grid->itemAtPosition(btn->mx+1,btn->my+1);
    if(btn->mx+1<sizex[diff] and btn->my+1<sizey[diff]){btn_r[4] = qobject_cast<sbutton*>(item[4]->widget());
        if(btn_r[4]->ar1 ==0)
        {
            btn_r[4]->ar1=10;
            btn_r[4]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        } else if(btn_r[4]->ar1 <9 and btn_r[4]->ar1 >=0)
        {
            btn_r[4]->ar1=10;
            btn_r[4]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        }
    }

    item[5] = grid->itemAtPosition(btn->mx-1,btn->my+1);
    if(btn->mx-1>=0 and btn->my+1<sizey[diff]){btn_r[5] = qobject_cast<sbutton*>(item[5]->widget());
        if(btn_r[5]->ar1 ==0)
        {
            btn_r[5]->ar1=10;
            btn_r[5]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        } else if(btn_r[5]->ar1 <9 and btn_r[5]->ar1 >=0)
        {
            btn_r[5]->ar1=10;
            btn_r[5]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        }
    }

    item[6] = grid->itemAtPosition(btn->mx+1,btn->my-1);
    if(btn->mx+1<sizex[diff] and btn->my-1>=0){btn_r[6] = qobject_cast<sbutton*>(item[6]->widget());
        if(btn_r[6]->ar1 ==0)
        {
            btn_r[6]->ar1=10;
            btn_r[6]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        } else if(btn_r[6]->ar1 <9 and btn_r[6]->ar1 >=0)
        {
            btn_r[6]->ar1=10;
            btn_r[6]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        }
    }

    item[7] = grid->itemAtPosition(btn->mx-1,btn->my-1);
    if(btn->mx-1>=0 and btn->my-1>=0){btn_r[7] = qobject_cast<sbutton*>(item[7]->widget());
        if(btn_r[7]->ar1 ==0)
        {
            btn_r[7]->ar1=10;
            btn_r[7]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        } else if(btn_r[7]->ar1 <9 and btn_r[7]->ar1 >=0)
        {
            btn_r[7]->ar1=10;
            btn_r[7]->signalHB();
            if (h == 0)
            {
                tmr->start();
                h++;
            }
            counter_q->display(flag[diff]);
            Window::slotWin();
        }
    }


}

void Window::slotUpdateTime()
{
    ct++;
    timer_q->display(ct);
}

void Window::slotCount1()
{
    flag[diff]--;
    if (h == 0)
    {
        tmr->start();
        h++;
    }
    counter_q->display(flag[diff]);
    Window::slotWin();
}

void Window::slotCount2()
{
    flag[diff]++;
    if (h == 0)
    {
        tmr->start();
        h++;
        Window::slotWin();
    }
    counter_q->display(flag[diff]);}

void Window::slotCount3()
{
    if (h == 0)
    {
        tmr->start();
        h++;
    }
    auto senderBtn = QObject::sender();
    sbutton* btn;
    btn = qobject_cast<sbutton*>(senderBtn);
    btn->ar1=10;
    Window::slotWin();

}

void Window::slotClose()
{
    tmr->stop();
    QMessageBox* q = new QMessageBox(this);
    q->setWindowTitle("Exit");
    q->show();
    q->setStyleSheet("color: white");
    q->setText("Вы точно хотите выйти?");
    q->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    int ret = q->exec();
    switch (ret) {
    case QMessageBox::Yes:
        this->close();
        break;
    case QMessageBox::No:
        if(h != 0 and win != 1 and lose != 1)
        {
            tmr->start();
        }
        break;
    }

}

void Window::slotGameOver()
{
    if(re == 0)
    {

        h = 1;
        lose = 1;
        lol = 100;
        QPixmap m ("game2.png");
        QIcon ii(m);
        r->setIcon(ii);
        ct=0;
        tmr->stop();
        QLayoutItem* item[sizex[diff]][sizey[diff]];
        sbutton* btn_r[sizex[diff]][sizey[diff]];
        for(int i = 0; i<sizex[diff]; i++){for(int j = 0; j<sizey[diff]; j++){
                item[i][j] = grid->itemAtPosition(i,j);
                btn_r[i][j] = qobject_cast<sbutton*>(item[i][j]->widget());
                btn_r[i][j]->signalOver();
            }
        }

    }}



void Window::slotWin()
{
    QLayoutItem* item[sizex[diff]][sizey[diff]];
    sbutton* btn_r[sizex[diff]][sizey[diff]];
    for(int i = 0; i<sizex[diff];i++)
    {
        for(int j = 0; j<sizey[diff];j++)
        {
            item[i][j] = grid->itemAtPosition(i,j);
            btn_r[i][j] = qobject_cast<sbutton*>(item[i][j]->widget());
            if(btn_r[i][j]->ar1==10)
            {
                bbbbbb++;
            }
        }

    }
    if(bbbbbb!=(sizex[diff]*sizey[diff])-bombs[diff])
    {
        bbbbbb=0;
    }
    else
    { if(lol!=100)
        {
            win=1;
            QPixmap m ("game1.png");
            QIcon ii(m);
            r->setIcon(ii);
            tmr->stop();
            for(int i = 0; i<sizex[diff];i++)
            {
                for(int j = 0; j<sizey[diff];j++)
                {
                    item[i][j] = grid->itemAtPosition(i,j);
                    btn_r[i][j] = qobject_cast<sbutton*>(item[i][j]->widget());
                    emit btn_r[i][j]->signalWin();
                    btn_r[i][j]->signalOver();
                }
            }
            h=0;
        }
    }
}

Window::~Window()
{
    delete r;
    delete exit;
    delete tmr;
    delete lvl;
    delete timer_q;
    delete counter_q;
    delete lvl_m;
    delete r_m;
    delete help_m;
}

void Window::slotInfo()
{
    tmr->stop();
    QMessageBox* q = new QMessageBox(this);
    q->setWindowTitle("Info");
    q->show();
    q->setStyleSheet("color: white");
    q->setText("Информация.");
    q->setInformativeText("Недоделанный сапёр. Правила игры: у вас есть X*Y полей и N бомб, все бомбы скрыты под полями. Откройте все незаминированные поля. При открывании вы можете увидеть бомбу, пустоту или число. Бомба - поражение, а число показывает, сколько бомб в ближайших 8 полях. Пустота показывает, что в ближайших полях нет бомб, поэтому эти поля будут автоматически открываться. Вы также можете выставлять флажки там, где по-вашему мнению есть бомбы, чтобы не забыть, где они и случайно на них не нажать. Управление: ЛКМ - открывает поле, ПКМ - ставит или убирает флажок, а также есть горячие клавиши (см. в меню). Внешний вид: внизу слева - счётчик оставшихся флажков, чуть правее - таймер, ещё правее - рестарт игры и ещё правее - переключение сложности. Сверху вы видите меню. По центру - поля с минами.");
    q->setStandardButtons(QMessageBox::Ok);
    int ret = q->exec();
    switch (ret) {
    case QMessageBox::Ok:
        if(h!=0 and win!=1 and lose != 1)
        {
            tmr->start();
        }
        break;
    }
}

void Window::slotHelp()
{
    QLayoutItem* item;
    sbutton* btn_r;
    int k = rand()%sizex[diff];
    int d = rand()%sizey[diff];
    item = grid->itemAtPosition(k,d);
    btn_r = qobject_cast<sbutton*>(item->widget());
    if(btn_r->ar1<9 and k<sizex[diff] and d<sizey[diff] and win == 0)
    {
        btn_r->ar1=10;
        btn_r->signalHB();
        if (h == 0 and win == 0)
        {
            tmr->start();
            h++;
        }
        counter_q->display(flag[diff]);
        Window::slotWin();
    }
    else if(win == 0)slotHelp();
    else if(win == 1)tmr->stop();
}

#include "sbutton.h"

sbutton::sbutton(int x, int y, int ar, QWidget* pwgt) : QLabel(pwgt)
{
    pb  = new customButton(this);
    QPixmap m ("button.png");
    QIcon ii(m);
    pb->setIcon(ii);
    pb->setIconSize(m.rect().size());
    this->setAlignment(Qt::AlignCenter);
    mx=x;
    my=y;

    QPixmap q0 ("0.png");
    QPixmap q1 ("1.png");
    QPixmap q2 ("2.png");
    QPixmap q3 ("3.png");
    QPixmap q4 ("4.png");
    QPixmap q5 ("5.png");
    QPixmap q6 ("6.png");
    QPixmap q7 ("7.png");
    QPixmap q8 ("8.png");
    QPixmap q9 ("b.png");


    switch (ar)
    {
    case 0:
        this->setPixmap(q0);
        break;
    case 1:
        this->setPixmap(q1);
        break;
    case 2:
        this->setPixmap(q2);
        break;
    case 3:
        this->setPixmap(q3);
        break;
    case 4:
        this->setPixmap(q4);
        break;
    case 5:
        this->setPixmap(q5);
        break;
    case 6:
        this->setPixmap(q6);
        break;
    case 7:
        this->setPixmap(q7);
        break;
    case 8:
        this->setPixmap(q8);
        break;
    case 9:
        this->setPixmap(q9);
        break;
    }

    ar2=ar;
    ar1=ar;

    connect(pb, &customButton::lclicked, this, &sbutton::slotButtonClicked);
    connect(pb, &customButton::rclicked1, this, &sbutton::slotButtonNoBomb);
    connect(pb, &customButton::rclicked2, this, &sbutton::slotButtonBomb);
    connect(this, &sbutton::signalHB, pb, &customButton::slotHB);
    connect(this, &sbutton::signalOver, pb, &customButton::slotOver);
    connect(this, &sbutton::signalWin, this, &sbutton::slotWin);

    QLayout* glo = new QGridLayout();
    glo->addWidget(pb);
    this->setLayout(glo);
    glo->setContentsMargins(0,0,0,0);

    QSizePolicy PolicyButton_1 = pb->sizePolicy();
    PolicyButton_1.setVerticalPolicy(QSizePolicy::Expanding);
    pb->setSizePolicy(PolicyButton_1);
}

int sbutton::setNumber()
{
    return ar2;
}

void sbutton::slotWin()
{
    if(ar2==9)
    {
        QPixmap m ("flag.png");
        this->setPixmap(m);
    }
}

void sbutton::slotButtonClicked()
{
    if(this->setNumber()==9)
    {
        QPixmap q10 ("bb.png");
        this->setPixmap(q10);
        emit signalBoom();
    }
    else if(this->setNumber()==0)
    {
        emit signalO();
    }
    emit signalNoBoom3();
}

void sbutton::slotButtonNoBomb()
{
    QPixmap m ("flag.png");
    QIcon ii(m);
    pb->setIcon(ii);
    pb->setIconSize(m.rect().size());
    if(ar2!=9)
    {
        QPixmap nb ("nb.png");
        this->setPixmap(nb);
    } else
    {
        this->setPixmap(m);
    }
    emit signalNoBoom1();
}

void sbutton::slotButtonBomb()
{
    QPixmap m ("button.png");
    QIcon ii(m);
    pb->setIcon(ii);
    pb->setIconSize(m.rect().size());
    QPixmap q0 ("0.png");
    QPixmap q1 ("1.png");
    QPixmap q2 ("2.png");
    QPixmap q3 ("3.png");
    QPixmap q4 ("4.png");
    QPixmap q5 ("5.png");
    QPixmap q6 ("6.png");
    QPixmap q7 ("7.png");
    QPixmap q8 ("8.png");
    QPixmap q9 ("b.png");
    switch (ar2)
    {
    case 0:
        this->setPixmap(q0);
        break;
    case 1:
        this->setPixmap(q1);
        break;
    case 2:
        this->setPixmap(q2);
        break;
    case 3:
        this->setPixmap(q3);
        break;
    case 4:
        this->setPixmap(q4);
        break;
    case 5:
        this->setPixmap(q5);
        break;
    case 6:
        this->setPixmap(q6);
        break;
    case 7:
        this->setPixmap(q7);
        break;
    case 8:
        this->setPixmap(q8);
        break;
    case 9:
        this->setPixmap(q9);
        break;
    }

    emit signalNoBoom2();
}

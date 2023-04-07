#include "custombutton.h"

customButton::customButton(QWidget* wgt) : QPushButton(wgt){}

void customButton::slotHB()
{ if(aw%2==0){
        hide();
        emit lclicked();}
}

void customButton::slotOver()
{
    hide();
}

void customButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton and aw%2 == 0)
    {
        slotHB();
    }
    else if(event->button() == Qt::RightButton and aw%2 == 1)
    {
        aw=0;
        emit rclicked2();
    }
    else if(event->button() == Qt::RightButton and aw%2 == 0)
    {
        aw=1;
        emit rclicked1();
    }

    QPushButton::mouseReleaseEvent(event);
}

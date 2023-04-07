#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include <QtWidgets>


class customButton : public QPushButton
{
    Q_OBJECT
public:
    customButton(QWidget* wgt = 0);
signals:
    void rclicked1();
    void rclicked2();
    void lclicked();
public slots:
    void slotHB();
    void slotOver();
protected:
    int aw = 0;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CUSTOMBUTTON_H

#ifndef MYLABEL_H
#define MYLABEL_H
#include<QWidget>
#include<QLineEdit>
#include<QMouseEvent>
class MyLEdit:public QLineEdit{
    Q_OBJECT
public:
    MyLEdit(QWidget*w):QLineEdit(w){}
protected:
    virtual void mouseReleaseEvent(QMouseEvent *e) {
        //Q_UNUSED(e);
        if(e->button()== Qt::LeftButton) {
            emit clicked(this);
        }

    }
signals:
    void clicked(MyLEdit*);
};
#endif // MYLABEL_H

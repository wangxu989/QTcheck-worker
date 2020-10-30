#ifndef MYLABEL_H
#define MYLABEL_H
#include<QWidget>
#include<QLineEdit>
#include<QMouseEvent>
//将program3完工界面中的QLineEdit提升为自己的类重载mouseReleaseEvent事件实现点击事件
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

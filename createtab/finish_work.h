#ifndef FINISH_WORK_H
#define FINISH_WORK_H

#include <QWidget>
#include<QHBoxLayout>
#include<myledit.h>
namespace Ui{
class finish_work;
}
namespace Program3 {
class finish_work : public QWidget
{
    Q_OBJECT

public:
    explicit finish_work(QWidget *parent = 0);
    ~finish_work();
//    QHBoxLayout* get_layout() {
//        return layout.data();
//    }
    bool setText(const QString&);
    QString text();

private:
    QSharedPointer<QHBoxLayout>layout;
    Ui::finish_work *ui;
    MyLEdit* now;
private slots:
    void label_change(MyLEdit*);
};
}

#endif // FINISH_WORK_H

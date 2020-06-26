#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QHBoxLayout>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
signals:
    void sendData();
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QHBoxLayout *H_layout;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

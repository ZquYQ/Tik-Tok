#ifndef ZHUYE_H
#define ZHUYE_H

#include "tianjiahaoyou.h"
#include <QWidget>
#include <QSqlDatabase>


namespace Ui {
class zhuye;
}

class zhuye : public QWidget
{
    Q_OBJECT
private:
    static zhuye *instance;
public:
    static zhuye* getInstance();
public:
     QSqlDatabase db;
    explicit zhuye(QWidget *parent = nullptr);
    ~zhuye();
signals:
    void sendData(const QString &data);
private slots:
    void on_BtnAdd_clicked();

private:
    Ui::zhuye *ui;
};

#endif // ZHUYE_H

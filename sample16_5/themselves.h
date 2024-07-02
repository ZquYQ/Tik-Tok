#ifndef THEMSELVES_H
#define THEMSELVES_H

#include <QWidget>
#include "frienditem.h"
#include "tcpclient.h"
#include <QSqlDatabase>
#include <QListWidgetItem>

namespace Ui {
class themselves;
}

class themselves : public QWidget
{
    Q_OBJECT
private:
    static themselves *instance;
public:
    static themselves* getInstance();

public:
    QSqlDatabase db;
    explicit themselves(QWidget *parent = nullptr);
    ~themselves();
public slots:
    void onListItemClicked(QListWidgetItem *item);
signals:
    void listItemClicked(QString nickname);


private:
    Ui::themselves *ui;
};


#endif // THEMSELVES_H

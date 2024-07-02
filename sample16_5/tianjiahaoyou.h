#ifndef TIANJIAHAOYOU_H
#define TIANJIAHAOYOU_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>


namespace Ui {
class tianjiahaoyou;
}

class tianjiahaoyou : public QWidget
{
    Q_OBJECT
public slots:
    void receiveData(const QString &data);
public:
    explicit tianjiahaoyou(QWidget *parent = nullptr);
    ~tianjiahaoyou();
    QSqlDatabase db;
private slots:
    void on_pushButton_clicked();

private:
    Ui::tianjiahaoyou *ui;
};

#endif // TIANJIAHAOYOU_H

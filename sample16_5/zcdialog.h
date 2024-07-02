#ifndef ZCDIALOG_H
#define ZCDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class ZCDialog;
}

class ZCDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZCDialog(QWidget *parent = nullptr);
    ~ZCDialog();
    QSqlDatabase db;
    QSqlQuery query;  //在创建对象时，系统会自动完成和数据库的关联
private slots:
    void on_btn_reg_clicked();

    void on_btn_quit_clicked();

private:
    Ui::ZCDialog *ui;
};

#endif // ZCDIALOG_H

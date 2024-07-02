#ifndef DENGLUDIALOG_H
#define DENGLUDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
extern QString zh;
class QSqlQuery;
namespace Ui {
class dengluDialog;
}

class dengluDialog : public QDialog
{
    Q_OBJECT
public:;
    QSqlDatabase db;
    //QSqlQuery query;  //在创建对象时，系统会自动完成和数据库的关联
    explicit dengluDialog(QWidget *parent = nullptr);
    ~dengluDialog();

private slots:

    void on_btn_inlog_clicked();

    void on_btn_reg_clicked();

    void on_btn_quit_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::dengluDialog *ui;
};

#endif // DENGLUDIALOG_H

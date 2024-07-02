#include "zcdialog.h"
#include "dengludialog.h"
#include "ui_zcdialog.h"
#include <QString>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

ZCDialog::ZCDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ZCDialog)
{
    ui->setupUi(this);
     this->setWindowTitle("用户注册");
    db=QSqlDatabase::addDatabase("QSQLITE");//QSQLINE--它来告诉系统，链接的数据库是sqlite3数据
        //连接成功，返回一个数据库对象（QSqlDatabase）
     db.setDatabaseName("D:/Administrator/Documents/build-sample16_5-Desktop_Qt_6_2_4_MinGW_64_bit-Debug/account&password.db");

    //如果想要进一步操作数据库，那么，就必须要进行数据库打开操作
    if(!db.open())
    {
        qDebug()<<"Error falied to open"<<db.lastError();
    }
    else
    {
        qDebug()<<"注册界面 Open 成功";
    }


}

ZCDialog::~ZCDialog()
{
    delete ui;
}

void ZCDialog::on_btn_reg_clicked()
{

    QString str1=ui->let_passwd1->text();
    QString str2=ui->let_passwd_2->text();
    QString str0=ui->let_account->text();
    if(str0.isEmpty()){ui->tishi->setText("请输入账号");return;}
    if(str0.length()<6){ui->tishi->setText("账号位数最少为6");return;}
    if(str1.isEmpty()){ui->tishi->setText("密码为空");return;}
    if(str1.length()<6){ui->tishi->setText("密码位数最少为6");return;}
    if(str2.isEmpty()){ui->tishi->setText("请确认密码");return;}
    if(str1!=str2){ui->tishi->setText("密码与确认密码不一致");return;}


    //插入操作
    QString str3=ui->let_account->text();
    QString str4=ui->let_passwd1->text();
    QString str5=ui->let_name->text();
    QSqlQuery query;
    QString sqlInsert = QString("insert into staff(account, password,name) values('%1','%2','%3');").arg(str3).arg(str4).arg(str5);

    if(!query.exec(sqlInsert))
    {
        qDebug()<<"insert table error"<<db.lastError();
    }
    else{
    dengluDialog *w=new dengluDialog;
    w->show();
    close();
    qDebug()<<str3<<"  "<<str4;
    }

}


void ZCDialog::on_btn_quit_clicked()
{
    dengluDialog *w=new dengluDialog;
    w->show();
    close();
}


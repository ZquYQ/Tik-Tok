#include "dengludialog.h"
#include "zcdialog.h"
#include "ui_dengludialog.h"
#include "mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>   //执行sql语句
#include <QSqlDatabase>  //数据库驱动
#include <QSqlError>

//创建数据库
//遍历数据库
//增删查改
QString zh;
dengluDialog::dengluDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dengluDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登录");

    db=QSqlDatabase::addDatabase("QSQLITE");//QSQLINE--它来告诉系统，链接的数据库是sqlite3数据
        //连接成功，返回一个数据库对象（QSqlDatabase）
    db.setDatabaseName("account&password.db");  //数据库文件后缀名为.db
    //QSqlQuery query;
    //如果想要进一步操作数据库，那么，就必须要进行数据库打开操作
    if(!db.open())
    {
        qDebug()<<"Error falied to open"<<db.lastError();
    }
    else
    {
        qDebug()<<"Open 成功";
    }
#if 0
    //定义一条创建表的sql语句 表名：staff 表中的字段：id name age
    QString sqlCreate=QString("create table staff(id integer primary key autoincrement,"
                                "account int,"
                                "password int);");
    if(!query.exec(sqlCreate))
   {
               qDebug()<<"create table error"<<db.lastError();
   }
#endif

#if 0
//插入操作
    QString sqlInsert=QString("insert into staff(account,password) values(123456,123456);");
    if(!query.exec(sqlInsert))
    {
        qDebug()<<"insert table error"<<db.lastError();
    }
#endif


}

dengluDialog::~dengluDialog()
{

    delete ui;
}

void dengluDialog::on_btn_inlog_clicked()
{

    //遍历寻找相等
    QSqlQuery query;
    //query(db);
    QString sqlSelect =QString("select * from staff;");

    if(!query.exec(sqlSelect))
    {
        qDebug()<<"insert data error 失败！！！"<<db.lastError();
    }else{
        while(query.next()){
            if((ui->let_name->text().toInt()==query.value("account").toInt()) && (ui->let_passwd->text().toInt()==query.value("password").toInt()) )
            {
                 zh=ui->let_name->text();
                 MainWindow *w=new MainWindow();
                 w->show();
                 close();
            }
        }
        ui->labtishi->setText("账号和密码不一致！！！");
    }

}


void dengluDialog::on_btn_reg_clicked()
{
    ZCDialog *w=new ZCDialog();
    w->show();
    close();
}


void dengluDialog::on_btn_quit_clicked()
{
    close();
}


void dengluDialog::on_checkBox_clicked(bool checked)
{
    if(checked){
    //隐藏
    ui->let_passwd->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    }
    else
    {
        ui->let_passwd->setEchoMode(QLineEdit::Normal);

    }
}


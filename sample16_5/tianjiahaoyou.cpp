#include "tianjiahaoyou.h"
#include "ui_tianjiahaoyou.h"
//#include "zhuye.h"

#include <QDebug>
#include <QSqlQuery>   //执行sql语句
#include <QSqlDatabase>  //数据库驱动
#include <QSqlError>


tianjiahaoyou::tianjiahaoyou(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tianjiahaoyou)
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



}


void tianjiahaoyou::receiveData(const QString &data)
{
    // 在这里使用接收到的data，例如更新界面上的显示
    ui->labname->setText(data); // 假设labFriendZh是tianjiahaoyou界面中用于显示好友账号的Label
}

tianjiahaoyou::~tianjiahaoyou()
{
    delete ui;
}

void tianjiahaoyou::on_pushButton_clicked()
{
    //插入操作
    int a=0;int b=0;
    QSqlQuery query;
    QString name;
    QString zh1 = ui->labname->text();
    QString zh2 = ui->lineEdit->text();
    //QString zh2name;

    QString sqlSelect1 =QString("select * from staff;");
    if(!query.exec(sqlSelect1))
    {
        qDebug()<<"insert data error 失败！！！"<<db.lastError();
    }else{
        while(query.next()){
            if((zh2==query.value("account").toString()))
            { a++;
                name=query.value("name").toString();}
        }
    }

    QString sqlSelect =QString("select * from friends;");
    if(!query.exec(sqlSelect))
    {
        qDebug()<<"insert data error 失败！！！"<<db.lastError();
    }else{
        while(query.next()){
            if((zh1==query.value("account").toString())&&(zh2==query.value("friends").toString()))b++;

        }
        if(b==0&&a!=0)
        {

            QString sqlInsert = "INSERT INTO friends(account, friends, name) VALUES(:zh1, :zh2 ,:name);";
            query.prepare(sqlInsert);
            query.bindValue(":zh1", zh1);
            query.bindValue(":zh2", zh2);
            query.bindValue(":name", name);
            if (!query.exec())
            {
                qDebug() << "Insert table error" << query.lastError();
            }
            ui->labTS->setText("添加"+name+"为好友成功！");
        }
        else ui->labTS->setText("账号不存在或已添加");
    }

}


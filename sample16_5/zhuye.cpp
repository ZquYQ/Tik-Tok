#include "zhuye.h"
#include "ui_zhuye.h"
#include"dengludialog.h"
#include <QSqlError>


zhuye* zhuye::instance = nullptr;
zhuye *zhuye::getInstance()
{
    if (!instance) {
        instance = new zhuye();
        qDebug()<<"!!!";
    }
    return instance;
}
zhuye::zhuye(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::zhuye)
{
    ui->setupUi(this);


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

    QSqlQuery query;
    //query(db);
    QString sqlSelect =QString("select * from staff;");

    if(!query.exec(sqlSelect))
    {
        qDebug()<<"insert data error 失败！！！"<<db.lastError();
    }else{while(query.next()){if((zh.toInt()==query.value("account").toInt()))
                ui->labName->setText(query.value("name").toString());}}
    ui->labZh->setText(zh);

}

zhuye::~zhuye()
{
    delete ui;
}

void zhuye::on_BtnAdd_clicked()
{

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


    QString data = ui->labZh->text(); // 获取ui->labZh的值

    tianjiahaoyou *w = new tianjiahaoyou(); // 创建tianjiahaoyou对象
    connect(this, &zhuye::sendData, w, &tianjiahaoyou::receiveData); // 将sendData信号连接到tianjiahaoyou类的receiveData槽函数
    emit sendData(data); // 发射sendData信号，传递data给tianjiahaoyou类
    w->show();
    close();
}

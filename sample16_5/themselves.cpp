#include "themselves.h"
#include "ui_themselves.h"
#include"dengludialog.h"
#include <QSqlQuery>
#include <QSqlError>



themselves* themselves::instance = nullptr;
themselves *themselves::getInstance()
{
    if (!instance) {
        instance = new themselves();
        qDebug()<<"!!!";
    }
    return instance;
}

themselves::themselves(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::themselves)
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
    QString sqlSelect =QString("select * from friends;");

    if(!query.exec(sqlSelect))
    {
        qDebug()<<"insert data error 失败！！！"<<db.lastError();
    }else{while(query.next())if((zh.toInt()==query.value("account").toInt()))

            {
                //界面
                QString a=query.value("name").toString();
                QString b=query.value("friends").toString();
                qDebug()<<a;
                qDebug()<<b;
            frienditem *friItem=new frienditem();
            friItem->setHeadImage("border-radius:30;border-image:url(:/images/images/YQ.jpg);");
            friItem->setnameImage(a);
            friItem->setnumImage(b);
            //QListWidgetItem
            QListWidgetItem *m_Item=new QListWidgetItem(ui->listWidget);

            //设置管理项. m_Item的宽高
            m_Item->setSizeHint(QSize(257,93));

            //将自定义的Qwidget--friItem,设置为m_Item的小部件。
            ui->listWidget->setItemWidget(m_Item,friItem);
            ui->listWidget->setStyleSheet("QListWidget::item:selected{background-color:rgb(200,200,200);}");
            }
        //去除滑动条
        ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//垂直
        ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平

    }
    connect(ui->listWidget, &QListWidget::itemClicked, this, &themselves::onListItemClicked);

}

// 在themselves.cpp中的onListItemClicked槽函数中传递昵称信息
void themselves::onListItemClicked(QListWidgetItem *item)
{
    frienditem *selectedItem = dynamic_cast<frienditem*>(ui->listWidget->itemWidget(item));
    QString nickname = selectedItem->getnameImage();
    QString nicknum = selectedItem->getnumImage();

    tcpclient *w = new tcpclient;
    w->setNickName(nickname);
    w->setNickNum(nicknum);
    w->setNickname(zh);
    w->show();
}

themselves::~themselves()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QLabel>
#include <QHostInfo>
#include <QList>
#include <QString>

struct ClientInfo {
    QString account;
    QString ip;
};
QMap<QString, QString> ipToAccountMap;
QString socketString;

// 比较运算符重载，用于比较两个 QHostAddress 对象的大小关系
bool operator<(const QHostAddress& address1, const QHostAddress& address2)
{
    return address1.toIPv4Address() < address2.toIPv4Address(); // 以 IPv4 地址为比较标准
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpServer=new QTcpServer(this);  //创建对象用于监听传入的TCP请求

    labListen=new QLabel("监听状态：");//创建一个QLabel用于显示监听状态
    labListen->setMinimumWidth(150);  //设置宽度
    ui->statusBar->addWidget(labListen);// 将lab加入ui状态栏中
    //同上只不过是显示socket状态
    labSocketState=new QLabel("Socket状态");
    labSocketState->setMidLineWidth(150);
    ui->statusBar->addWidget(labSocketState);

    QString hostName=QHostInfo::localHostName(); //获取本机名字
    QHostInfo hostInfo=QHostInfo::fromName(hostName); //通过名字获取本机地址
    //创建对象存储IPV4地址
    QString localIP;
    foreach (const auto& item, hostInfo.addresses()) {
        if(item.protocol()==QAbstractSocket::IPv4Protocol)
        {
            localIP=item.toString();
            ui->comboIP->addItem(localIP);
        }
    }
    //TCPServer发生改变调用do_newConnection函数,
    connect(tcpServer,&QTcpServer::newConnection,this,&MainWindow::do_newConnection);
}

MainWindow::~MainWindow()
{
    if(tcpSocket != nullptr && (tcpSocket->state()==QAbstractSocket::ConnectedState))
        tcpSocket->disconnectFromHost();
    if(tcpServer->isListening())
        tcpServer->close();
    delete ui;
}


void MainWindow::on_actStart_triggered()
{
    QString IP=ui->comboIP->currentText();
    quint16 port=ui->spinPort->value();
    QHostAddress address(IP);
    tcpServer->listen(address,port);

    ui->textEdit->appendPlainText("**开始监听**");
    ui->textEdit->appendPlainText("**服务器地址："+tcpServer->serverAddress().toString());
    ui->textEdit->appendPlainText("**服务器端口号："+QString::number(tcpServer->serverPort()));

    ui->actStart->setEnabled(false);
    ui->actStop->setEnabled(true);
    labListen->setText("监听状态：正在监听");
}


//创建子进程
void MainWindow::do_newConnection()
{
    QTcpSocket* newSocket = tcpServer->nextPendingConnection();
    socketString = QString("QTcpSocket(0x%1)").arg((quintptr)newSocket, 0, 16);

    qDebug() << socketString;  // 输出 QTcpSocket(0x24793197b60)
    qDebug()<<newSocket;
    qDebug()<<"!!!!!";
    clientSockets.append(newSocket);//将新的客户端套接字添加到列表中

    //qDebug()<<"1";
    // ... 连接信号和槽 ...

    connect(newSocket,&QTcpSocket::connected,this,&MainWindow::do_connected);
    connect(newSocket,&QTcpSocket::disconnected,this,&MainWindow::do_disconnected);
    connect(newSocket,&QTcpSocket::readyRead,this,&MainWindow::do_readyRead);
    connect(newSocket,&QTcpSocket::stateChanged,this,&MainWindow::do_stateChanged);

}

//连接成功，显示信息及客户端信息

//这个没用
void MainWindow::do_connected()
{
    qDebug()<<"2";
    ui->textEdit->appendPlainText("**client socket connected**");   //显示套接字连接成功
    ui->textEdit->appendPlainText("**peer address:"+tcpSocket->peerAddress().toString()); //获取IP显示到textedit中
    ui->textEdit->appendPlainText("**peer port："+QString::number(tcpSocket->peerPort())); //获取客户端端口号显示
}
//提示，连接失败
void MainWindow::do_disconnected()
{

    ui->textEdit->appendPlainText("**client socket disconnected**");
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    if(socket)
    {

        // ClientInfo client;
        // for (auto it = ipToAccountMap.begin(); it != ipToAccountMap.end(); ) {
        //     if (socketString == it.key()) {
        //         it = ipToAccountMap.erase(it);
        //     } else {
        //         ++it;
        //     }
        // }

        socket->deleteLater();
    }
}

//可读时（已经接收到数据之后），接收数据
void MainWindow::do_readyRead()
{
    //先连先发消息，后连后发消息
    //qDebug()<<"zero";
    QTcpSocket* senderSocket = qobject_cast<QTcpSocket*>(sender());

    QByteArray data = senderSocket->readAll();
    //qDebug()<<data;
    //qDebug()<<"zero!";
    int spacePos = data.indexOf(' ');
    int secondSpacePos = data.indexOf(' ', spacePos + 1);
    int thirdSpacePos = data.indexOf(' ', secondSpacePos + 1);
    QString firstPart;
    QString secPart;
    // 如果找到了空格
    //qDebug()<<"one";
    firstPart = data.left(spacePos);
    secPart = data.mid(spacePos + 1, secondSpacePos - spacePos - 1);
    QString substringBetweenSpaces = data.mid(secondSpacePos + 1, thirdSpacePos - secondSpacePos - 1);
    ui->labname1->setText(firstPart);
    ui->labname2->setText(secPart);
    ui->labname->setText(substringBetweenSpaces);//操作


    qDebug()<<data;
    //qDebug()<<"two";

    ClientInfo client;
    bool key=0;
    client.ip = socketString;
    qDebug()<<socketString;
    client.account = substringBetweenSpaces; // 从数据流中解析得到账号信息
    for (auto it = ipToAccountMap.begin(); it != ipToAccountMap.end(); ++it){
        if(firstPart==it.value()&&socketString==it.key())
            key=1;
    }
    if(key==0)ipToAccountMap.insert(client.ip, client.account);
    //qDebug()<<"three";
    //获取发送数据的socket对象
    //QTcpSocket* senderSocket = qobject_cast<QTcpSocket*>(sender());

    if(!data.isNull())
    {
        // 读取接收到的数据
        //QByteArray data = senderSocket->readAll();

        // 获取发送者的IP地址和端口号信息
        QString senderInfo = "From " + senderSocket->peerAddress().toString() + ":" + QString::number(senderSocket->peerPort()) + " ";
        // 将接收到的数据转换为QString格式
        QString message = QString::fromUtf8(data);
        //添加打印
        //qDebug()<<"接收到"<<message;

        // 在服务器界面上显示发送者信息和消息内容
        ui->textEdit->appendPlainText(senderInfo + message);
        // ui->textEdit

        // 将发送者信息附加到消息前
        data.prepend(senderInfo.toUtf8());
        QString  targetIP;
        for (auto it = ipToAccountMap.begin(); it != ipToAccountMap.end(); ++it)
        {
            qDebug()<<it.value()<<" "<<it.key();
            if (it.value() == ui->labname1->text())
            {
                qDebug()<<"sure";
                targetIP  = it.key();
                break; // 找到目标账号对应的IP地址后跳出循环
            }
        }

        if (!targetIP.isNull())
        {
            qDebug() << "Target account: " << firstPart;
            qDebug() << "IP address: " << targetIP;
            // 遍历客户端socket列表，向除原发送者外的所有客户端发送包含发送者信息的消息数据
            for(QTcpSocket* clientSocket : clientSockets)
            {
                qDebug()<<clientSocket;
                qDebug()<<targetIP;
                if(QString("QTcpSocket(0x%1)").arg((quintptr)clientSocket, 0, 16) == targetIP) // 确保不会将数据发送回原发送者
                {

                    clientSocket->write(data);
                }
            }
        }
        else
        {
            qDebug() << "Target account not found";
        }


    }
}



//状态改变时，调用函数，并在labe内显示状态
void MainWindow::do_stateChanged(QAbstractSocket::SocketState state)
{
    switch (state)
    {
    case QAbstractSocket::UnconnectedState:
        labSocketState->setText("socket状态：UnconnectedState"); //未连接
        break;
    case QAbstractSocket::HostLookupState:
        labSocketState->setText("socket状态：HostLookupState");  //正在查找主机
        break;
    case QAbstractSocket::ConnectingState:
        labSocketState->setText("socket状态：ConnectingState"); //正在连接
        break;
    case QAbstractSocket::ConnectedState:
        labSocketState->setText("socket状态：ConnectedState");  //已连接
        break;
    case QAbstractSocket::BoundState:
        labSocketState->setText("socket状态：BoundState");  //已绑定
        break;
    case QAbstractSocket::ClosingState:
        labSocketState->setText("socket状态：ClosingState");  //正在关闭
        break;
    case QAbstractSocket::ListeningState:
        labSocketState->setText("socket状态：ListeningState"); //正在监听
    }

}


void MainWindow::on_actStop_triggered()
{
    if(tcpServer->isListening())//正在监听
    {
        if(tcpSocket != nullptr && (tcpSocket->state()==QAbstractSocket::ConnectedState)) //不空且已经连接
            tcpSocket->disconnectFromHost(); //断联
        ui->actStart->setEnabled(true);
        ui->actStop->setEnabled(false);
        labListen->setText("监听状态：已停止");
    }
}


void MainWindow::on_actClear_triggered()
{
    ui->textEdit->clear();
}


void MainWindow::on_btnSend_clicked()
{
    if(tcpSocket==nullptr) //判空
    {
        ui->textEdit->appendPlainText("tcpSocket==nullptr！");
        return;
    }

    QString msg=ui->editMsg->text();  //获取发送信息
    ui->textEdit->appendPlainText("[out] "+msg);  //添加out前缀
    ui->editMsg->clear();   //清除信息框
    ui->editMsg->setFocus(); //聚焦

    QByteArray str=msg.toUtf8();  //确定为utf8的格式
    str.append('\n');  //换行
    tcpSocket->write(str);//写入换行
}



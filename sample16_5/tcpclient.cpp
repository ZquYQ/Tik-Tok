#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QTcpSocket>
#include <QHostInfo>

tcpclient::tcpclient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tcpclient)
{
    ui->setupUi(this);

    tcpSocket=new QTcpSocket(this);   //创建TCPSocket对象
    //显示状态
    labSocketState=new QLabel("Socket状态");
    labSocketState->setMidLineWidth(150);
    ui->statusBar->addWidget(labSocketState);
    labSocketState->setStyleSheet("QLabel { color: white; }");
    //获取ip
    QString hostName=QHostInfo::localHostName();
    QHostInfo hostInfo=QHostInfo::fromName(hostName);
    //ipv4
    QString localIP;
    foreach (const auto& item, hostInfo.addresses()) {
        if(item.protocol()==QAbstractSocket::IPv4Protocol)
        {
            localIP=item.toString();
            break;
        }
    }

    // QString addr=ui->comboServer->currentText();
    // quint16 port=ui->spinPort->value();
    // tcpSocket->connectToHost(addr,port);

    //链接时调用四个函数

    connect(tcpSocket,&QTcpSocket::connected,this,&tcpclient::do_connected);
    connect(tcpSocket,&QTcpSocket::disconnected,this,&tcpclient::do_disconnected);
    connect(tcpSocket,&QTcpSocket::readyRead,this,&tcpclient::do_readyRead);
    connect(tcpSocket,&QTcpSocket::stateChanged,this,&tcpclient::do_stateChanged);


    QString toolbarStyle("QToolBar QToolButton { color: rgb(255, 255, 255); }");
    ui->toolBar->setStyleSheet(toolbarStyle);
}

tcpclient::~tcpclient()
{
    delete ui;
}



void tcpclient::do_connected()
{
    ui->textEdit->appendPlainText("**已连接服务器**");
    ui->textEdit->appendPlainText("**peer address:"+tcpSocket->peerAddress().toString());
    ui->textEdit->appendPlainText("**peer port："+QString::number(tcpSocket->peerPort()));
    ui->actConnect->setEnabled(false);
    ui->actDisconnect->setEnabled(true);


}

void tcpclient::do_disconnected()
{
    ui->textEdit->appendPlainText("**服务器disconnected**");
    ui->actConnect->setEnabled(true);
    ui->actDisconnect->setEnabled(false);
}

void tcpclient::do_readyRead()
{
    while(tcpSocket->canReadLine())
        ui->textEdit->appendPlainText("[in] "+tcpSocket->readLine());
}

void tcpclient::do_stateChanged(QAbstractSocket::SocketState state)
{
    switch (state)
        {
        case QAbstractSocket::UnconnectedState:
            labSocketState->setText("socket状态：UnconnectedState");
            break;
        case QAbstractSocket::HostLookupState:
            labSocketState->setText("socket状态：HostLookupState");
            break;
        case QAbstractSocket::ConnectingState:
            labSocketState->setText("socket状态：ConnectingState");
            break;
        case QAbstractSocket::ConnectedState:
            labSocketState->setText("socket状态：ConnectedState");
            break;
        case QAbstractSocket::BoundState:
            labSocketState->setText("socket状态：BoundState");
            break;
        case QAbstractSocket::ClosingState:
            labSocketState->setText("socket状态：ClosingState");
            break;
        case QAbstractSocket::ListeningState:
            labSocketState->setText("socket状态：ListeningState");
        }
}


void tcpclient::on_actConnect_triggered()
{
    QString addr=ui->comboServer->currentText();
    quint16 port=ui->spinPort->value();
    tcpSocket->connectToHost(addr,port);
    qDebug() << "Server Address: " << addr;
    qDebug() << "Port: " << port;
    on_btnSend_clicked();
}


void tcpclient::on_actDisconnect_triggered()
{
    if(tcpSocket->state()==QAbstractSocket::ConnectedState)
        tcpSocket->disconnectFromHost(); //断连
}


void tcpclient::on_actClear_triggered()
{
    ui->textEdit->clear();
}


void tcpclient::on_btnSend_clicked()
{
    QString msg=ui->editMsg->text();
    QString zh=ui->labNum->text();
    QString name=ui->labName->text();
    QString Name=ui->labname->text();
    ui->textEdit->appendPlainText("[out] "+msg);
    ui->textEdit->appendPlainText("");
    ui->editMsg->clear();
    ui->editMsg->setFocus();

    QByteArray str=msg.toUtf8();
    QByteArray str2=zh.toUtf8();
    QByteArray str3=name.toUtf8();
    QByteArray str4=Name.toUtf8();
    str.append('\n');
    qDebug()<<"传输的数据="<<str2+" "+str3+" "+str4+" "+str;
    if(  tcpSocket->write(str2+" "+str3+" "+str4+" "+str)==-1)
    {
        qDebug("发送失败");
    }

}

void tcpclient::setNickName(QString nickname)
{
    ui->labName->setText(nickname);
}

void tcpclient::setNickNum(QString nicknum)
{
    ui->labNum->setText(nicknum);
}

void tcpclient::setNickname(QString nickname)
{
    ui->labname->setText(nickname);
}


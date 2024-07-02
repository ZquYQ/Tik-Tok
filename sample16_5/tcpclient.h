#ifndef TCPCLIENT_H
#define TCPCLIENT_H


#include <QMainWindow>
#include <QAbstractSocket>

class QTcpSocket;
class QLabel;
QT_BEGIN_NAMESPACE
namespace Ui {class tcpclient;}
QT_END_NAMESPACE
class tcpclient : public QMainWindow
{
    Q_OBJECT
private:
    QTcpSocket *tcpSocket=nullptr;

    QLabel *labSocketState;
public:
    explicit tcpclient(QWidget *parent = nullptr);
    ~tcpclient();
public slots:
    void setNickName(QString nickname);
    void setNickNum(QString nicknum);
    void setNickname(QString nickname);
private slots:

    void do_connected();
    void do_disconnected();
    void do_readyRead();
    void do_stateChanged(QAbstractSocket::SocketState state);
    void on_actConnect_triggered();

    void on_actDisconnect_triggered();

    void on_actClear_triggered();

    void on_btnSend_clicked();
private:
    Ui::tcpclient *ui;

};

#endif // TCPCLIENT_H


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QList>
#include <QString>
#include <QThread>
#include <QTcpSocket>
class QTcpServer;
//class QTcpSocket;
class QLabel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket=nullptr;
    QList<QTcpSocket*> clientSockets;
    QLabel *labListen;//监听状态
    QLabel *labSocketState;
private:
    QMap<QString, QTcpSocket*> accountToSocketMap; // 从账号映射到QTcpSocket的字典
    //void endMessageToAccount(const QString& account, const QByteArray& data)
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actStart_triggered();

    void do_newConnection();
    void do_connected();
    void do_disconnected();
    void do_readyRead();
    void do_stateChanged(QAbstractSocket::SocketState state);
    void on_actStop_triggered();

    void on_actClear_triggered();

    void on_btnSend_clicked();

private:
    Ui::MainWindow *ui;
};


// class TcpClientThread : public QThread
// {
//     Q_OBJECT

// public:
//     TcpClientThread(qintptr socketDescriptor);
//     void run() override;

// signals:
//     void error(QTcpSocket::SocketError socketError);

// private:
//     qintptr socketDescriptor;
// };
#endif // MAINWINDOW_H

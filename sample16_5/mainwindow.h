#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include "tmyvideowidget.h"
#include "zhuye.h"
#include "tcpclient.h"
#include "themselves.h"
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMediaPlayer *player;
    QString durationTime;
    QString positionTime;
    int key=0;
public:
    QSqlDatabase bd;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void do_playbackStateChanged(QMediaPlayer::PlaybackState newState);

    void do_positionChanged(qint64 position);

    void do_durationChanged(qint64 duration);

    void on_btnAdd_clicked();

    void on_btnPlay_clicked();

    void on_btnSound_clicked();

    void on_sliderVolumn_valueChanged(int value);

    void on_pushButton_clicked();

    void on_sliderPosition_valueChanged(int value);


    void on_comboBoxBS_activated(int index);

    void on_BtnUP_clicked();

    void on_BtnDown_clicked();

    void on_BtnZY_clicked();

    void on_BtnQQ_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dengludialog.h"
#include <QFileDialog>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //setFixedSize(width(), height());

    ui->labname->setText(zh);

    player=new QMediaPlayer(this);
    QAudioOutput *audioOutput=new QAudioOutput(this);

    player->setAudioOutput(audioOutput);
    player->setVideoOutput(ui->videoWidget);
    ui->videoWidget->setMediaPlayer(player);

    connect(player,&QMediaPlayer::playbackStateChanged,this,&MainWindow::do_playbackStateChanged);
    connect(player,&QMediaPlayer::positionChanged,this,&MainWindow::do_positionChanged);
    connect(player,&QMediaPlayer::durationChanged,this,&MainWindow::do_durationChanged);

    bd=QSqlDatabase::addDatabase("QSQLITE");//QSQLINE--它来告诉系统，链接的数据库是sqlite3数据
        //连接成功，返回一个数据库对象（QSqlDatabase）
    bd.setDatabaseName("Video.db");  //数据库文件后缀名为.db
    //QSqlQuery query;
    //如果想要进一步操作数据库，那么，就必须要进行数据库打开操作
    if(!bd.open())
    {
        qDebug()<<"Error falied to open"<<bd.lastError();
    }
    else
    {
        qDebug()<<"Open 成功";
    }
    //qDebug()<<QDir::currentPath()<<"绝对路径！！！";
   //地址 ./douyin./1.mp4
#if 0
    QSqlQuery query;
    QString sqlCreate=QString("create table staff(id integer primary key autoincrement,"
                                "dizhi QString);");
    if(!query.exec(sqlCreate))
    {
        qDebug()<<"create table error"<<db.lastError();
    }
#endif

//播放
    QSqlQuery query1(bd);
    QUrl url;int a=0;
    QString sqlSelect = QString("select * from shipin;");
    if (query1.exec(sqlSelect)) {
        while (query1.next()) {
            QString dz = query1.value("dizhi").toString();
            QString na = query1.value("name").toString();
            if(a==0){url = QUrl::fromLocalFile(dz);a++;key++;
                ui->labCurMedia->setText(na);}
        }
    } else {
        qDebug() << "Error executing query: " << query1.lastError().text();
    }
    player->setSource(url);
    player->play();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_playbackStateChanged(QMediaPlayer::PlaybackState newState)
{
    if(newState==QMediaPlayer::PausedState)
    ui->btnPlay->setIcon(QIcon(":/images/images/ZT.png"));
    if(newState==QMediaPlayer::PlayingState)
    ui->btnPlay->setIcon(QIcon(":/images/images/BF.png"));
}

void MainWindow::do_positionChanged(qint64 position)
{
    if(ui->sliderPosition->isSliderDown())
        return;

    ui->sliderPosition->setSliderPosition(position);
    int secs=position/1000;
    int mins=secs/60;
    secs%=60;
    positionTime=QString::asprintf("%d:%d",mins,secs);
    ui->LabRatio->setText(positionTime+"/"+durationTime);
}

void MainWindow::do_durationChanged(qint64 duration)
{
    ui->sliderPosition->setMaximum(duration);

    int secs=duration/1000;
    int mins=secs/60;
    secs%=60;
    durationTime=QString::asprintf("%d:%d",mins,secs);
    ui->LabRatio->setText(positionTime+"/"+durationTime);
}

void MainWindow::on_btnAdd_clicked()
{
    QString curPath=QDir::homePath();
    QString dlgTile="选择视频文件";
    QString filter="视频文件(*.wmv, *.mp4);;所有文件(*.*)";
    QString aFile=QFileDialog::getOpenFileName(this,dlgTile,curPath,filter);

    if(aFile.isEmpty())
        return;

    QFileInfo fileInfo(aFile);
    ui->labCurMedia->setText(fileInfo.fileName());
    player->setSource(QUrl::fromLocalFile(aFile));
    player->play();
}

//按键的播放和暂停
void MainWindow::on_btnPlay_clicked()
{
    if(player->playbackState()==QMediaPlayer::PausedState){
        player->play();
        qDebug()<<player->playbackState();
        //ui->btnPlay->setIcon(QIcon(":/images/images/ZT.png"));
        return;}
    if(player->playbackState()==QMediaPlayer::PlayingState){
        player->pause();
        qDebug()<<player->playbackState();
        //ui->btnPlay->setIcon(QIcon(":/images/images/BF.png"));
        return;}
}

void MainWindow::on_btnSound_clicked()
{
    bool mute=player->audioOutput()->isMuted();
    player->audioOutput()->setMuted(!mute);
    if(mute)
        ui->btnSound->setIcon(QIcon(":/images/images/YP.png"));
    else
        ui->btnSound->setIcon(QIcon(":/images/images/YP-NO.png"));
}


void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    player->audioOutput()->setVolume(value/100.0);
}


void MainWindow::on_pushButton_clicked()
{
    // ui->videoWidget->setWindowFlags (Qt::Window);
    // ui->videoWidget->showFullScreen ();
    ui->videoWidget->setFullScreen(true);
}


void MainWindow::on_sliderPosition_valueChanged(int value)
{
    player->setPosition(value);
}


void MainWindow::on_comboBoxBS_activated(int index)
{

    if(ui->comboBoxBS->currentText().toDouble() == 1.0)
    {
        player->setPlaybackRate(1.0);

    }

    if(ui->comboBoxBS->currentText().toDouble() == 1.25)
    {
        player->setPlaybackRate(1.25);

    }

    if(ui->comboBoxBS->currentText().toDouble() == 1.5)
    {
        player->setPlaybackRate(1.5);

    }

    if(ui->comboBoxBS->currentText().toDouble() == 2.0)
    {
        player->setPlaybackRate(2.0);

    }

}


void MainWindow::on_BtnUP_clicked()
{


    bd=QSqlDatabase::addDatabase("QSQLITE");//QSQLINE--它来告诉系统，链接的数据库是sqlite3数据
        //连接成功，返回一个数据库对象（QSqlDatabase）
    bd.setDatabaseName("Video.db");  //数据库文件后缀名为.db
    //QSqlQuery query;
    //如果想要进一步操作数据库，那么，就必须要进行数据库打开操作
    if(!bd.open())
    {
        qDebug()<<"Error falied to open"<<bd.lastError();
    }
    else
    {
        qDebug()<<"Open 成功";
    }


    QSqlQuery query1(bd);
    QUrl url;int a=0;
    QString sqlSelect = QString("select * from shipin;");
    if (query1.exec(sqlSelect)) {
        while (query1.next()) {
            a++;
            QString dz = query1.value("dizhi").toString();
            QString na = query1.value("name").toString();
            if(a+1==key){url = QUrl::fromLocalFile(dz);
                ui->labCurMedia->setText(na);key--;break;}
        }
    } else {
        qDebug() << "Error executing query: " << query1.lastError().text();
    }
    player->setSource(url);
    player->play();
}


void MainWindow::on_BtnDown_clicked()
{

    bd=QSqlDatabase::addDatabase("QSQLITE");//QSQLINE--它来告诉系统，链接的数据库是sqlite3数据
        //连接成功，返回一个数据库对象（QSqlDatabase）
    bd.setDatabaseName("Video.db");  //数据库文件后缀名为.db
    //QSqlQuery query;
    //如果想要进一步操作数据库，那么，就必须要进行数据库打开操作
    if(!bd.open())
    {
        qDebug()<<"Error falied to open"<<bd.lastError();
    }
    else
    {
        qDebug()<<"Open 成功";
    }

    QSqlQuery query1(bd);
    QUrl url;int a=0;
    QString sqlSelect = QString("select * from shipin;");
    if (query1.exec(sqlSelect)) {
        while (query1.next()) {
            a++;
            QString dz = query1.value("dizhi").toString();
            QString na = query1.value("name").toString();
            if(a==key+1){url = QUrl::fromLocalFile(dz);/*qDebug()<<"!!!"<<a<<" "<<key;*/
                ui->labCurMedia->setText(na);key++;break;}
        }
    } else {
        qDebug() << "Error executing query: " << query1.lastError().text();
    }
    player->setSource(url);
    player->play();

}


void MainWindow::on_BtnZY_clicked()
{
    zhuye::getInstance()->show();
}


void MainWindow::on_BtnQQ_clicked()
{
    themselves::getInstance()->show();
}


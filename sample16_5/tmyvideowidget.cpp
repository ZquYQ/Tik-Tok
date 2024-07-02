#include "tmyvideowidget.h"
#include <QMouseEvent>
TMyVideoWidget::TMyVideoWidget(QWidget *parent):QVideoWidget(parent)
{
    resize(761,371);
    setFixedSize(width(), height());

}

void TMyVideoWidget::setMediaPlayer(QMediaPlayer *player)
{
    m_player=player;
}


//点屏幕，暂停和播放
void TMyVideoWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(m_player->playbackState()==QMediaPlayer::PlayingState)
            m_player->pause();
        else
            m_player->play();
    }
    // if(event->button()==Qt::RightButton){
    //     if(m_player->playbackState()==QMediaPlayer::PlayingState)
    //         m_player->pause();
    //     else
    //         m_player->play();qDebug()<<"成功";}
    QVideoWidget::mousePressEvent(event);
}


//esc以及全屏
void TMyVideoWidget::keyPressEvent(QKeyEvent *event)
{
     if((event->key()==Qt::Key_Escape) && isFullScreen() )
     {
        setFullScreen(false);

        //setWindowFlags (Qt::SubWindow);
        //showNormal ();
        qDebug()<<"esc";return;
     }
      if(event->key()==Qt::Key_Space)
      {
          if(m_player->playbackState()==QMediaPlayer::PausedState){
              m_player->play();
              qDebug()<<m_player->playbackState();
              //ui->btnPlay->setIcon(QIcon(":/images/images/ZT.png"));
             return;}
         if(m_player->playbackState()==QMediaPlayer::PlayingState){
              m_player->pause();
              qDebug()<<m_player->playbackState();
              //ui->btnPlay->setIcon(QIcon(":/images/images/BF.png"));
              return;}
      }
     QVideoWidget::keyPressEvent(event);

}

#ifndef TMYVIDEOWIDGET_H
#define TMYVIDEOWIDGET_H

#include <QVideoWidget>
#include <QMediaPlayer>

class TMyVideoWidget : public QVideoWidget
{
    Q_OBJECT
private:
    QMediaPlayer *m_player;
public:
    TMyVideoWidget(QWidget *parent = nullptr);
    void setMediaPlayer(QMediaPlayer *player);
    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;//控制全屏
    virtual void mousePressEvent(QMouseEvent *event) override;//控制暂停，播放

};



#endif // TMYVIDEOWIDGET_H

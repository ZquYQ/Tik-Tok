#ifndef FRIENDITEM_H
#define FRIENDITEM_H

#include <QWidget>

namespace Ui {
class frienditem;
}

class frienditem : public QWidget
{
    Q_OBJECT

public:
    explicit frienditem(QWidget *parent = nullptr);
    ~frienditem();
    frienditem(const QString& nameImage);
    QString getnameImage() const;
    QString getnumImage() const;
private:
    Ui::frienditem *ui;
public:
    void setHeadImage(QString imgpath);
    void setnameImage(QString imgpath);
    void setnumImage(QString imgpath);
};

#endif // FRIENDITEM_H

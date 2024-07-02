#include "frienditem.h"
#include "ui_frienditem.h"

frienditem::frienditem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frienditem)
{
    ui->setupUi(this);
}

frienditem::~frienditem()
{
    delete ui;
}

void frienditem::setHeadImage(QString imgpath)
{
    ui->label->setStyleSheet(imgpath);
}

void frienditem::setnameImage(QString imgpath)
{
    ui->labname->setText(imgpath);
}
void frienditem::setnumImage(QString imgpath)
{
    ui->labnum->setText(imgpath);
}
QString frienditem::getnameImage() const {
    return ui->labname->text();

}
QString frienditem::getnumImage() const {
    return ui->labnum->text();

}



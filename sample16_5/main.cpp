//#include "mainwindow.h"
#include "dengludialog.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    dengluDialog w;
    w.show();
    return a.exec();
}

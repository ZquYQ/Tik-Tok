QT       += core gui
QT += multimedia
QT += multimediawidgets
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT   +=core gui sql

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dengludialog.cpp \
    frienditem.cpp \
    main.cpp \
    mainwindow.cpp \
    tcpclient.cpp \
    themselves.cpp \
    tianjiahaoyou.cpp \
    tmyvideowidget.cpp \
    zcdialog.cpp \
    zhuye.cpp

HEADERS += \
    dengludialog.h \
    frienditem.h \
    mainwindow.h \
    tcpclient.h \
    themselves.h \
    tianjiahaoyou.h \
    tmyvideowidget.h \
    zcdialog.h \
    zhuye.h

FORMS += \
    dengludialog.ui \
    frienditem.ui \
    mainwindow.ui \
    tcpclient.ui \
    themselves.ui \
    tianjiahaoyou.ui \
    zcdialog.ui \
    zhuye.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=

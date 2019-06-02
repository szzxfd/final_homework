#-------------------------------------------------
#
# Project created by QtCreator 2019-05-22T18:45:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo_2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    basictower.cpp \
    enemy.cpp \
    plistreader.cpp \
    waypoint.cpp \
    towerposition.cpp \
    basicbullet.cpp

HEADERS += \
        mainwindow.h \
    basictower.h \
    enemy.h \
    plistreader.h \
    towerposition.h \
    utility.h \
    waypoint.h \
    basicbullet.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resourses.qrc

DISTFILES += \
    image/bullet/image 2410.png \
    image/bullet/image 4927.png \
    image/bullet/image 4964.png \
    image/bullet/image 5038.png \
    image/bullet/image 8219.png


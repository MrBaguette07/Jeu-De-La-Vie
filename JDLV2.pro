QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    src/


HEADERS += \
    grillewidget.h \
    jeuLogique.h \
    mainwindow.h
    ui_mainwindow.h

SOURCES += \
    main.cpp \
    grillewidget.cpp \
    jeuLogique.cpp \
    mainwindow.cpp

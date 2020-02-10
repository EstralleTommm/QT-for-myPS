#-------------------------------------------------
#
# Project created by QtCreator 2019-11-25T10:34:04
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myPs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tlm.cpp \
    paintwidget.cpp \
    videosurface.cpp

HEADERS  += mainwindow.h \
    tlm.h \
    paintwidget.h \
    videosurface.h

FORMS    += mainwindow.ui

RESOURCES += \
    ico.qrc

TRANSLATIONS = lang_English.ts \
               lang_Chinese.ts

DISTFILES +=

RC_ICONS =myico.ico

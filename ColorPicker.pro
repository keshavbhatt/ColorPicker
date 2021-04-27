#-------------------------------------------------
#
# Project created by QtCreator 2019-12-02T14:20:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = color-picker
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

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

CONFIG += c++11

SOURCES += \
        colordialog.cpp \
        main.cpp \
        mainwindow.cpp \
        previewer.cpp \
        settings.cpp

HEADERS += \
        colordialog.h \
        gridlayoututil.h \
        mainwindow.h \
        previewer.h \
        settings.h

FORMS += \
        mainwindow.ui \
        pattern.ui \
        settings.ui


RESOURCES += \
    breeze.qrc \
    icons.qrc \
    resources.qrc

# Default rules for deployment.
isEmpty(PREFIX){
 PREFIX = /usr
}

BINDIR  = $$PREFIX/bin
DATADIR = $$PREFIX/share

target.path = $$BINDIR

icon.files = icons/color-picker.png
icon.path = $$DATADIR/icons/hicolor/512x512/apps/

desktop.files = color-picker.desktop
desktop.path = $$DATADIR/applications/

INSTALLS += target icon desktop

#-------------------------------------------------
# ImuDataProcesser is used for data segmentation after data acquisition.
# Author : Flame
# Last change: 2019-05-03
# E-mail : 547453159@qq.com
# Language : C++
#-------------------------------------------------

QT       += core gui
QT       += charts network
QT       += multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImuDAQ
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

CONFIG += c++11
CONFIG += console warn_off

SOURCES += \
    ImuEncode.pb.cc \
    ImuSocket.cpp \
    ImuMatrix.cpp \
    LpSetConfiguration.cpp \
    ImuDAQ.cpp \
    ImuLineseries.cpp \
    ImuVerticalline.cpp \
    ImuChart.cpp \
    CsvWriter.cpp \
    CsvReader.cpp \
    ImuData.cpp \
    ImuVideoSurface.cpp \
    ImuViewFinder.cpp \
    Main.cpp \
    Menu.cpp \
    ImuDaqDialog.cpp \
    ImuProcesserWidget.cpp \
    ImageWidget.cpp

HEADERS += \
    OpenMAT-1.3.5/include/DeviceListItem.h \
    OpenMAT-1.3.5/include/ImuData.h \
    OpenMAT-1.3.5/include/LpmsDefinitions.h \
    OpenMAT-1.3.5/include/LpmsSensorI.h \
    OpenMAT-1.3.5/include/LpmsSensorManagerI.h \
    ImuEncode.pb.h \
    ImuSocket.h \
    ImuMatrix.h \
    LpSetConfiguration.h \
    ImuDAQ.h \
    ImuLineseries.h \
    ImuVerticalline.h \
    ImuChart.h \
    CsvReader.h \
    CsvWriter.h \
    ImuData.h \
    ImuVideoSurface.h \
    ImuViewFinder.h \
    Menu.h \
    ImuDaqDialog.h \
    ImuProcesserWidget.h \
    ImageWidget.h

FORMS += \
        widget.ui \
    dialog.ui \
    ImuViewFinder.ui \
    Menu.ui

LIBS += -L$$PWD/OpenMAT-1.3.5/lib/x86 -lLpSensor
LIBS += -L$$PWD/google/lib -llibprotobufd

RC_ICONS += settings_48px.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

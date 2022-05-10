QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    driver.cpp \
    greenhouse.cpp \
    greenhouselist.cpp \
    httpget.cpp \
    httppost.cpp \
    loader.cpp \
    main.cpp \
    mainwindow.cpp \
    monitor.cpp \
    sensordata.cpp

HEADERS += \
    HTTPInterface.h \
    IDriver.h \
    ILoader.h \
    IMonitor.h \
    driver.h \
    greenhouse.h \
    greenhouselist.h \
    httpget.h \
    httppost.h \
    loader.h \
    mainwindow.h \
    monitor.h \
    sensordata.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
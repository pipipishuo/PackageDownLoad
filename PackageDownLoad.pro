QT       += core gui network

QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
LIBS+= -lz
SOURCES += \
    downloadfile.cpp \
    main.cpp \
    mainwindow.cpp \
    parse.cpp \
    datamanager.cpp

HEADERS += \
    downloadfile.h \
    mainwindow.h \
    parse.h \
    datamanager.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

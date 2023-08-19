QT += quick virtualkeyboard
QT -= gui

TEMPLATE = lib
CONFIG += c++20 dl

TARGET = interfacelayer
DESTDIR = $$PWD/../Executable
LIBS += -L$$PWD/../Executable -luicommon -lservice

INCLUDEPATH += $$PWD/../UICommon \
               $$PWD/../ServiceWrapper/include \
               $$PWD/../ServiceWrapper/include/Common \
               $$PWD/../ServiceWrapper/include/Wifi \

SOURCES += \
    Common/AbstractInterface.cpp \
    Wifi/WifiAdapter.cpp \
    Wifi/WifiIF.cpp

HEADERS += \
    Common/AbstractInterface.h \
    Wifi/WifiIF.h

DISTFILES +=

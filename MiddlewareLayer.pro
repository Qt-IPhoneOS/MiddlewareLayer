QT += quick virtualkeyboard
QT -= gui

TEMPLATE = lib
CONFIG += c++20 dl

TARGET = middlewarelayer
DESTDIR = $$PWD/../Executable
LIBS += -L$$PWD/../Executable -luicommon -lservice

INCLUDEPATH += $$PWD/../UICommon \
               $$PWD/../UICommon/FeatureClass \
               $$PWD/../Services/include \
               $$PWD/../Services/include/Common \
               $$PWD/../Services/include/Wifi \

SOURCES += \
    Common/AbstractInterface.cpp \
    Wifi/WifiAdapter.cpp \
    Wifi/WifiDevice.cpp \
    Wifi/WifiIFConnect.cpp \
    Wifi/WifiInterface.cpp

HEADERS += \
    Common/AbstractInterface.h \
    Wifi/WifiDevice.h \
    Wifi/WifiInterface.h

DISTFILES +=

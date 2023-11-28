QT += quick virtualkeyboard
QT -= gui

TEMPLATE = lib
CONFIG += c++20 dl

TARGET = middlewarelayer
DESTDIR = $$PWD/../Executable
LIBS += -L$$PWD/../Executable -luicommon -lservice

INCLUDEPATH += $$PWD/../Apps/UICommon \
               $$PWD/../Apps/UICommon/Feature \
               $$PWD/../Services/include \
               $$PWD/../Services/include/Common \
               $$PWD/../Services/include/Wifi \
               $$PWD/../Services/include/SystemSetting \
               $$PWD/../Services/include/Common/BaseClass

SOURCES += \
    Common/AbstractInterface.cpp \
    Wifi/WifiAdapter.cpp \
    Wifi/WifiAdapterConnect.cpp \
    Wifi/WifiDevice.cpp \
    SystemSetting/SystemSettingAdapter.cpp \
    SystemSetting/SystemSettingConnect.cpp

HEADERS += \
    Common/AbstractInterface.h \
    Wifi/WifiAdapter.h \
    Wifi/WifiDevice.h \ 
    SystemSetting/SystemSettingAdapter.h
    
DISTFILES +=

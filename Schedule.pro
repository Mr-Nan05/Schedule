QT       += core gui
Qt5Multimediad.lib
Qt5Multimedia.lib
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    date.cpp \
    date.cpp \
    event.cpp \
    file.cpp \
    for_remind.cpp \
    incident.cpp \
    list.cpp \
    main.cpp \
    remind_time_set.cpp \
    widget.cpp

HEADERS += \
    date.h \
    event.h \
    file.h \
    for_remind.h \
    incident.h \
    list.h \
    remind_time_set.h \
    widget.h

FORMS += \
    event.ui \
    for_remind.ui \
    incident.ui \
    list.ui \
    remind_time_set.ui \
    widget.ui

TRANSLATIONS += \
    Schedule_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    notepad.pro

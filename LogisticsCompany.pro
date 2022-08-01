QT       += core gui sql

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
    capasity_order_dialog.cpp \
    capasity_ships_dialog.cpp \
    dialog_edit.cpp \
    main.cpp \
    mainwindow.cpp \
    order_dialog.cpp \
    otshet_dialog.cpp \
    port_dialog.cpp \
    port_dialog_edit.cpp \
    raspis.cpp \
    route_dialog.cpp \
    schedule_dialog.cpp \
    ship_dialog.cpp \
    statictics_dialog.cpp \
    weather_dialog.cpp

HEADERS += \
    capasity_order_dialog.h \
    capasity_ships_dialog.h \
    dialog_edit.h \
    mainwindow.h \
    order_dialog.h \
    otshet_dialog.h \
    port_dialog.h \
    port_dialog_edit.h \
    raspis.h \
    route_dialog.h \
    schedule_dialog.h \
    ship_dialog.h \
    statictics_dialog.h \
    weather_dialog.h

FORMS += \
    capasity_order_dialog.ui \
    capasity_ships_dialog.ui \
    dialog_edit.ui \
    mainwindow.ui \
    order_dialog.ui \
    otshet_dialog.ui \
    port_dialog.ui \
    raspis.ui \
    route_dialog.ui \
    schedule_dialog.ui \
    ship_dialog.ui \
    statictics_dialog.ui \
    weather_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resurs.qrc

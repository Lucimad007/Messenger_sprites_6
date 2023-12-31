QT       += core gui network uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcontacteventfilter.cpp \
    apimanager.cpp \
    app.cpp \
    channel.cpp \
    chatprototypeeventfilter.cpp \
    errordialog.cpp \
    group.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    user.cpp

HEADERS += \
    addcontacteventfilter.h \
    apimanager.h \
    app.h \
    channel.h \
    chatprototypeeventfilter.h \
    errordialog.h \
    group.h \
    mainwindow.h \
    message.h \
    user.h

FORMS += \
    Login.ui \
    addcontact.ui \
    app.ui \
    chatprototype.ui \
    createjoin.ui \
    errordialog.ui \
    mainwindow.ui \
    message.ui \
    options.ui \
    profile.ui \
    register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

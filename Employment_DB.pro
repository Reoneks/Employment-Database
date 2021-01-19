QT       += core gui sql charts

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
    addplaceoflearning.cpp \
    addpreviousjob.cpp \
    addvacancy.cpp \
    admineditvacancy.cpp \
    changenews.cpp \
    createmail.cpp \
    database.cpp \
    findemployer.cpp \
    jobapplications.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    news.cpp \
    privateoffice.cpp \
    registration.cpp \
    resume.cpp \
    userstatistics.cpp

HEADERS += \
    addplaceoflearning.h \
    addpreviousjob.h \
    addvacancy.h \
    admineditvacancy.h \
    changenews.h \
    createmail.h \
    database.h \
    findemployer.h \
    jobapplications.h \
    login.h \
    mainwindow.h \
    news.h \
    privateoffice.h \
    registration.h \
    resume.h \
    userstatistics.h

FORMS += \
    addplaceoflearning.ui \
    addpreviousjob.ui \
    addvacancy.ui \
    admineditvacancy.ui \
    changenews.ui \
    createmail.ui \
    findemployer.ui \
    jobapplications.ui \
    login.ui \
    mainwindow.ui \
    news.ui \
    privateoffice.ui \
    registration.ui \
    resume.ui \
    userstatistics.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Media.qrc

win32:RC_ICONS += $$PWD/images/Logo.ico

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    convertcode.cpp \
    creatorwindow.cpp \
    filework.cpp \
    generator.cpp \
    history.cpp \
    main.cpp \
    horizonjuicercreator.cpp \
    readandwritejson.cpp \
    removecommitwindow.cpp \
    runtime.cpp \
    setting.cpp

HEADERS += \
    about.hpp \
    convertcode.hpp \
    creatorwindow.hpp \
    filework.hpp \
    generator.hpp \
    history.hpp \
    horizonjuicercreator.hpp \
    readandwritejson.hpp \
    removecommitwindow.hpp \
    runtime.hpp \
    setting.hpp

FORMS += \
    about.ui \
    creatorwindow.ui \
    history.ui \
    horizonjuicercreator.ui \
    removecommitwindow.ui \
    runtime.ui \
    setting.ui

TRANSLATIONS += \
    HorizonJuicerCreator_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L"C:/Users/Marco Nie/Library/boost_1_72_0/stage/lib/" \
        -llibboost_filesystem-mgw81-mt-x32-1_72 \
        -llibboost_regex-mgw81-mt-x32-1_72

INCLUDEPATH += "C:/Users/Marco Nie/Library/boost_1_72_0"
DEPENDPATH += "C:/Users/Marco Nie/Library/boost_1_72_0"

DISTFILES +=

RESOURCES +=

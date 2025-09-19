QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    convertcode.cpp \
    creatorwindow.cpp \
    filework.cpp \
    generatepro.cpp \
    history.cpp \
    main.cpp \
    horizonjuicercreator.cpp \
    readandwritejson.cpp \
    removecommit.cpp \
    removecommitwindow.cpp \
    setting.cpp

HEADERS += \
    about.hpp \
    convertcode.hpp \
    creatorwindow.hpp \
    filework.hpp \
    generatepro.h \
    history.hpp \
    horizonjuicercreator.hpp \
    readandwritejson.hpp \
    removecommit.hpp \
    removecommitwindow.hpp \
    setting.hpp

FORMS += \
    about.ui \
    creatorwindow.ui \
    history.ui \
    horizonjuicercreator.ui \
    removecommitwindow.ui \
    setting.ui

TRANSLATIONS += \
    HorizonJuicerCreator_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: {
    LIBS += -L"C:/Users/Marco Nie/Library/boost_1_72_0/stage/lib/" \
                    -llibboost_filesystem-mgw81-mt-x32-1_72 \
                    -llibboost_regex-mgw81-mt-x32-1_72
    INCLUDEPATH += "C:/Users/Marco Nie/Library/boost_1_72_0"
    DEPENDPATH += "C:/Users/Marco Nie/Library/boost_1_72_0"
    RC_ICONS = ./hjc.ico
}

macx: {
    LIBS += -L"/Users/marconie/libs/boost_1_75_0/stage/lib/" \
                    -lboost_filesystem \
                    -lboost_regex
    INCLUDEPATH += /Users/marconie/libs/boost_1_75_0
    DEPENDPATH += /Users/marconie/libs/boost_1_75_0
    ICON = ./hjc.icns
}

DISTFILES +=

RESOURCES += \
    resourse.qrc \
    qdarkstyle/dark/style.qrc

macx: QMAKE_LIBS_OPENGL = -framework OpenGL


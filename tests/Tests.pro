QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  main.cpp \
    filtertests.cpp \
    recipestoragetests.cpp \
    recipestoretests.cpp

HEADERS += \
    filtertests.h \
    recipestoragetests.h \
    recipestoretests.h

INCLUDEPATH += ../

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ThomChefCore/release/ -lThomChefCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ThomChefCore/debug/ -lThomChefCore
else:unix: LIBS += -L$$OUT_PWD/../ThomChefCore/ -lThomChefCore

INCLUDEPATH += $$PWD/../ThomChefCore
DEPENDPATH += $$PWD/../ThomChefCore

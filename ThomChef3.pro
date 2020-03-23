#-------------------------------------------------
#
# Project created by QtCreator 2013-08-15T18:29:21
#
#-------------------------------------------------

QT      += core gui
QT 	+= network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ThomChef3
TEMPLATE = app
ICON = icone.icns


SOURCES +=  main.cpp \
            old-core/data.cpp \
            old-core/recette.cpp \
            old-core/XMLParser.cpp \
            old-views/mainwindow.cpp \
            old-views/ajouterrecette.cpp \
            old-views/gererconfiguration.cpp \
            old-views/listeingredients.cpp \
            views/addrecipe.cpp \
            views/thomchefwindow.cpp \
            views/viewutils.cpp


HEADERS  += old-core/data.h \
            old-core/recette.h \
            old-core/XMLParser.h \
            old-views/mainwindow.h \
            old-views/ajouterrecette.h \
            old-views/gererconfiguration.h \
            old-views/listeingredients.h \
            views/addrecipe.h \
            views/thomchefwindow.h \
            views/viewutils.h

FORMS    += old-views/mainwindow.ui \
            old-views/ajouterrecette.ui \
            old-views/gererconfiguration.ui \
            old-views/listeingredients.ui \
            views/addrecipe.ui \
            views/thomchefwindow.ui

OTHER_FILES +=  Resources/recettes.xml \
                Resources/AModifier.txt \
                Resources/icone.icns

INCLUDEPATH += old-views/
INCLUDEPATH += old-core/
INCLUDEPATH += views/

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build/core/release/ -lThomChefCore.1.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build/core/debug/ -lThomChefCore.1.0.0
else:unix: LIBS += -L$$PWD/build/core/ -lThomChefCore.1.0.0

INCLUDEPATH += $$PWD/core
DEPENDPATH += $$PWD/core

#-------------------------------------------------
#
# Project created by QtCreator 2013-08-15T18:29:21
#
#-------------------------------------------------

QT       += core gui
QT 	+= network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ThomChef3
TEMPLATE = app
ICON = icone.icns


SOURCES += main.cpp\
        mainwindow.cpp \
    data.cpp \
    recette.cpp \
    XMLParser.cpp \
    ajouterrecette.cpp \
    gererconfiguration.cpp \
    listeingredients.cpp

HEADERS  += mainwindow.h \
    data.h \
    recette.h \
    XMLParser.h \
    ajouterrecette.h \
    gererconfiguration.h \
    listeingredients.h

FORMS    += mainwindow.ui \
    ajouterrecette.ui \
    gererconfiguration.ui \
    listeingredients.ui

OTHER_FILES += \
    recettes.xml \
    AModifier.txt \
    icone.icns

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


SOURCES += main.cpp\
    conversions.cpp \
        mainwindow.cpp \
    data.cpp \
    recette.cpp \
    XMLParser.cpp \
    ajouterrecette.cpp \
    gererconfiguration.cpp \
    listeingredients.cpp \
    libs/pugixml-1.9/src/pugixml.cpp \
    recipecollection.cpp \
    recipecollectionserializer.cpp


HEADERS  += mainwindow.h \
    conversions.h \
    data.h \
    recette.h \
    XMLParser.h \
    ajouterrecette.h \
    gererconfiguration.h \
    listeingredients.h \
    libs/pugixml-1.9/src/pugiconfig.hpp \
    libs/pugixml-1.9/src/pugixml.hpp \
    recipecollection.h \
    recipecollectionserializer.h

FORMS    += mainwindow.ui \
    ajouterrecette.ui \
    gererconfiguration.ui \
    listeingredients.ui

OTHER_FILES += \
    recettes.xml \
    AModifier.txt \
    icone.icns

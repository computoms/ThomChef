QT -= gui
QT += core

TEMPLATE = lib
DEFINES += THOMCHEFCORE_LIBRARY

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
    configuration.cpp \
    Storage/configurationstoragefile.cpp \
    conversions.cpp \
    ingredient.cpp \
    ingredientfilter.cpp \
    recipe.cpp \
    Storage/recipestoragefile.cpp \
    recipestore.cpp \
    ../libs/pugixml-1.9/src/pugixml.cpp

HEADERS += \
    Storage/recipestorage.h \
    ThomChefCore_global.h \
    configuration.h \
    Storage/configurationstoragefile.h \
    conversions.h \
    definitions.h \
    ingredient.h \
    ingredientfilter.h \
    recipe.h \
    Storage/recipestoragefile.h \
    recipestore.h \
    thomchefcore.h \
    ../libs/pugixml-1.9/src/pugixml.hpp \
    ../libs/pugixml-1.9/src/pugiconfig.hpp

INCLUDEPATH += ../

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

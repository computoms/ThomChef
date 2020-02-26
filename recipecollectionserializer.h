#ifndef RECETTECOLLECTIONSERIALIZER_H
#define RECETTECOLLECTIONSERIALIZER_H
#include <string>
#include "recipecollection.h"

#include "libs/pugixml-1.9/src/pugixml.hpp"

class RecipeCollectionSerializer
{
public:
    RecipeCollectionSerializer();

    RecipeCollection read(std::string filename);
    Recette readRecipe(pugi::xml_node recipeNode);

    bool serializeTo(std::string filename, RecipeCollection recipeCollection);
    pugi::xml_node serializeRecipe(Recette recipe);
};

#endif // RECETTECOLLECTIONSERIALIZER_H

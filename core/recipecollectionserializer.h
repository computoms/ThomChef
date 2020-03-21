#ifndef RECETTECOLLECTIONSERIALIZER_H
#define RECETTECOLLECTIONSERIALIZER_H
#include <string>
#include "recipecollection.h"
#include "recipe.h"

#include "libs/pugixml-1.9/src/pugixml.hpp"

class RecipeCollectionSerializer
{
public:
    RecipeCollectionSerializer();

    RecipeCollection read(std::string filename);
    Recipe readRecipe(pugi::xml_node recipeNode);

    bool serializeTo(std::string filename, RecipeCollection recipeCollection);
    pugi::xml_node serializeRecipe(Recipe recipe);
};

#endif // RECETTECOLLECTIONSERIALIZER_H

#ifndef RECETTECOLLECTIONSERIALIZER_H
#define RECETTECOLLECTIONSERIALIZER_H
#include <string>
#include "recipestore.h"
#include "recipe.h"

#include "libs/pugixml-1.9/src/pugixml.hpp"

class RecipeStoreSerializer
{
public:
    RecipeStoreSerializer();

    RecipeStore read(std::string filename);
    Recipe readRecipe(std::string recipeSerialization);

    bool serializeTo(std::string filename, RecipeStore recipeCollection);
    std::string serializeRecipe(Recipe recipe);
};

#endif // RECETTECOLLECTIONSERIALIZER_H

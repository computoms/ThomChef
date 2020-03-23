#ifndef RECETTECOLLECTIONSERIALIZER_H
#define RECETTECOLLECTIONSERIALIZER_H
#include <string>
#include "recipe.h"

#include "libs/pugixml-1.9/src/pugixml.hpp"

class FileRecipeStorage
{
public:
    FileRecipeStorage(std::string filename);

    Recipe readRecipe(std::string recipeSerialization);
    std::string serializeRecipe(Recipe recipe);

    std::vector<Recipe> read();
    bool save(std::vector<Recipe> recipes);

private:
    std::string m_filename;

};

#endif // RECETTECOLLECTIONSERIALIZER_H

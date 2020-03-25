#ifndef RECETTECOLLECTIONSERIALIZER_H
#define RECETTECOLLECTIONSERIALIZER_H
#include <string>
#include "recipestorage.h"

#include "libs/pugixml-1.9/src/pugixml.hpp"

/**
 * @brief The FileRecipeStorage class handles storage of the database data into
 * a flat xml file.
 */
class RecipeStorageFile : public RecipeStorage
{
public:
    RecipeStorageFile(std::string filename);
    virtual ~RecipeStorageFile() {}

    Recipe readRecipe(std::string recipeSerialization) const;
    std::string serializeRecipe(Recipe recipe) const;

    virtual std::vector<Recipe> read() const override;
    virtual bool save(std::vector<Recipe> recipes) const override;

private:
    std::string m_filename;

};

#endif // RECETTECOLLECTIONSERIALIZER_H

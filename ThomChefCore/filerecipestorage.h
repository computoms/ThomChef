#ifndef RECETTECOLLECTIONSERIALIZER_H
#define RECETTECOLLECTIONSERIALIZER_H
#include <string>
#include "recipe.h"

#include "libs/pugixml-1.9/src/pugixml.hpp"

class RecipeStorage
{
public:
    virtual std::vector<Recipe> read() const = 0;
    virtual bool save(std::vector<Recipe> recipes) const = 0;
};

/**
 * @brief The FileRecipeStorage class handles storage of the database data into
 * a flat xml file.
 */
class FileRecipeStorage : public RecipeStorage
{
public:
    FileRecipeStorage(std::string filename);

    Recipe readRecipe(std::string recipeSerialization) const;
    std::string serializeRecipe(Recipe recipe) const;

    virtual std::vector<Recipe> read() const override;
    virtual bool save(std::vector<Recipe> recipes) const override;

private:
    std::string m_filename;

};

#endif // RECETTECOLLECTIONSERIALIZER_H

#ifndef RECIPESTORAGE_H
#define RECIPESTORAGE_H
#include <vector>
#include "ThomChefCore/recipe.h"

/**
 * @brief The RecipeStorage class is the interface of a storage for recipes.
 */
class RecipeStorage
{
public:
    virtual std::vector<Recipe> read(time_t &maxId) const = 0;
    virtual bool save(std::vector<Recipe> recipes, time_t maxId) const = 0;
};

#endif // RECIPESTORAGE_H

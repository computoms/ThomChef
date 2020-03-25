#ifndef RECIPESTORAGE_H
#define RECIPESTORAGE_H
#include <vector>
#include "ThomChefCore/recipe.h"

class RecipeStorage
{
public:
    virtual std::vector<Recipe> read() const = 0;
    virtual bool save(std::vector<Recipe> recipes) const = 0;
};

#endif // RECIPESTORAGE_H

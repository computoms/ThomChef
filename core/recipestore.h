#ifndef RECIPESTORE_H
#define RECIPESTORE_H

#include "recipe.h"
#include <vector>

class RecipeStore
{
public:
    RecipeStore();

    int getNumberOfRecipes() const;
    Recipe getRecipe(int recipeIndex) const;

    void addRecipe(Recipe recette);

private:
    std::vector<Recipe> recipes;
};

#endif // RECIPESTORE_H

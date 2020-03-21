#ifndef RECETTECOLLECTION_H
#define RECETTECOLLECTION_H

#include "recipe.h"
#include <vector>

class RecipeCollection
{
public:
    RecipeCollection();

    int getNumberOfRecipes() const;
    Recipe getRecipe(int recipeIndex) const;

    void addRecipe(Recipe recette);

private:
    std::vector<Recipe> recipes;
};

#endif // RECETTECOLLECTION_H

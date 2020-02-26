#include "recipecollection.h"

RecipeCollection::RecipeCollection()
{

}

int RecipeCollection::getNumberOfRecipes() const
{
    return recipes.size();
}

Recette RecipeCollection::getRecipe(int recipeIndex) const
{
    if (recipeIndex < 0 || recipeIndex >= recipes.size())
        return Recette(); // TODO Hanlde errors
    return recipes[recipeIndex];
}

void RecipeCollection::addRecipe(Recette recette)
{
    recipes.push_back(recette);
}

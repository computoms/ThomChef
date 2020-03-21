#include "recipecollection.h"

RecipeCollection::RecipeCollection()
{

}

int RecipeCollection::getNumberOfRecipes() const
{
    return recipes.size();
}

Recipe RecipeCollection::getRecipe(int recipeIndex) const
{
    if (recipeIndex < 0 || recipeIndex >= recipes.size())
        return Recipe(); // TODO Hanlde errors
    return recipes[recipeIndex];
}

void RecipeCollection::addRecipe(Recipe recette)
{
    recipes.push_back(recette);
}

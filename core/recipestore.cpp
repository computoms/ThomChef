#include "recipestore.h"

RecipeStore::RecipeStore()
{

}

int RecipeStore::getNumberOfRecipes() const
{
    return recipes.size();
}

Recipe RecipeStore::getRecipe(int recipeIndex) const
{
    if (recipeIndex < 0 || recipeIndex >= (int)recipes.size())
        throw std::invalid_argument("Recipe of index " + std::to_string(recipeIndex) + " not found");
    return recipes[recipeIndex];
}

void RecipeStore::addRecipe(Recipe recette)
{
    recipes.push_back(recette);
}

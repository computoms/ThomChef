#ifndef RECIPESTORE_H
#define RECIPESTORE_H

#include "recipe.h"
#include <vector>
#include "filerecipestorage.h"

class RecipeStore
{
public:
    RecipeStore(std::shared_ptr<FileRecipeStorage> storage);

    void initialize();

    int getNumberOfRecipes() const;
    Recipe getRecipe(int recipeIndex) const;
    Recipe findRecipeByName(std::string name) const;

    void addRecipe(Recipe recette);

private:
    std::vector<Recipe> m_recipes;
    std::shared_ptr<FileRecipeStorage> m_storage;

};

#endif // RECIPESTORE_H

#ifndef RANDOMRECIPESELECTOR_H
#define RANDOMRECIPESELECTOR_H
#include "recipestore.h"

class RandomRecipeSelector
{
public:
    RandomRecipeSelector(RecipeStore *store);

    std::vector<Recipe> selectRecipes(int numberOfRecipes);
    std::vector<Ingredient> getListOfIngredients();

private:
    RecipeStore *m_store;
    std::vector<Recipe> m_generatedRecipes;
};

#endif // RANDOMRECIPESELECTOR_H

#ifndef RANDOMRECIPESELECTOR_H
#define RANDOMRECIPESELECTOR_H
#include "recipestore.h"

class RandomRecipeSelector
{
public:
    RandomRecipeSelector(RecipeStore *store);

    std::vector<Recipe> selectRecipes(int numberOfRecipes);
    void addRecipe(const Recipe &recipe);
    void removeRecipe(const Recipe &recipe);
    std::vector<Ingredient> getListOfIngredients();

private:
    std::vector<Ingredient> unifiesIngredients(std::vector<Ingredient> ingredients) const;
    bool findIngredientAndAddQuantity(std::vector<Ingredient> &uniqueIngredients, const Ingredient &newIngredient) const;
    std::vector<int> generateRandomIntegers(int maxValue, int count) const;

private:
    RecipeStore *m_store;
    std::vector<Recipe> m_generatedRecipes;
};

#endif // RANDOMRECIPESELECTOR_H

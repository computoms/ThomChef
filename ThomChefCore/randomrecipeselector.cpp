#include "randomrecipeselector.h"

RandomRecipeSelector::RandomRecipeSelector(RecipeStore *store):
    m_store     (store)
{

}

std::vector<Recipe> RandomRecipeSelector::selectRecipes(int numberOfRecipes)
{
    if (m_store->getNumberOfRecipes() < numberOfRecipes)
        throw std::invalid_argument("The number of recipes to be generated must be lower than the total number of recipes.");
    m_generatedRecipes.clear();
    // TODO implement random selection
    for (int i = 0; i < numberOfRecipes; ++i)
        m_generatedRecipes.push_back(m_store->getRecipe(i));
    return m_generatedRecipes;
}

std::vector<Ingredient> RandomRecipeSelector::getListOfIngredients()
{
    std::vector<Ingredient> ingredients;
    for (auto &recipe : m_generatedRecipes)
    {
        for (int i = 0; i < recipe.getNumberOfIngredients(); ++i)
            ingredients.push_back(recipe.getIngredient(i));
    }
    // TODO Clean-up ingredients to avoid duplicates
    return ingredients;
}

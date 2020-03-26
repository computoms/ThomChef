#include "randomrecipeselector.h"
#include <random>

RandomRecipeSelector::RandomRecipeSelector(RecipeStore *store):
    m_store     (store)
{

}

std::vector<Recipe> RandomRecipeSelector::selectRecipes(int numberOfRecipes)
{
    if (m_store->getNumberOfRecipes() < numberOfRecipes)
        throw std::invalid_argument("The number of recipes to be generated must be lower than the total number of recipes.");
    m_generatedRecipes.clear();
    std::vector<int> randomIndexes = generateRandomIntegers(m_store->getNumberOfRecipes() - 1, numberOfRecipes);
    for (int i = 0; i < (int) randomIndexes.size(); ++i)
        m_generatedRecipes.push_back(m_store->getRecipe(randomIndexes[i]));
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

    return unifiesIngredients(ingredients);
}

std::vector<Ingredient> RandomRecipeSelector::unifiesIngredients(std::vector<Ingredient> ingredients) const
{
    std::vector<Ingredient> uniqueIngredients;
    for (const auto &ing : ingredients)
    {
        if (!findIngredientAndAddQuantity(uniqueIngredients, ing))
            uniqueIngredients.push_back(ing);
    }
    return uniqueIngredients;
}

bool RandomRecipeSelector::findIngredientAndAddQuantity(std::vector<Ingredient> &uniqueIngredients, const Ingredient &newIngredient) const
{
    for (size_t i = 0; i < uniqueIngredients.size(); ++i)
    {
        if (uniqueIngredients[i].getName() == newIngredient.getName()
            && uniqueIngredients[i].getUnit() == newIngredient.getUnit())
        {
            double newQuantity = newIngredient.getQuantity() + uniqueIngredients[i].getQuantity();
            uniqueIngredients[i] = Ingredient(uniqueIngredients[i].getName(),
                                              newQuantity,
                                              uniqueIngredients[i].getUnit());
            return true;
        }
    }
    return false;
}

std::vector<int> RandomRecipeSelector::generateRandomIntegers(int maxValue, int count) const
{
    std::vector<int> randomIndexes;
    std::vector<int> distribution;
    for (int i = 0; i <= maxValue; ++i)
        distribution.push_back(i);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(distribution.begin(), distribution.end(), generator);

    for (int i = 0; i < count; ++i)
        randomIndexes.push_back(distribution[i]);
    return randomIndexes;
}

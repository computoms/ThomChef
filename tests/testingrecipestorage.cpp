#include "testingrecipestorage.h"

std::vector<Recipe> TestingRecipeStorage::read() const
{
    return m_recipes;
}

bool TestingRecipeStorage::save(std::vector<Recipe> recipes) const
{
    m_recipes = recipes;
    return true;
}

void TestingRecipeStorage::reset()
{
    m_recipes.clear();
}

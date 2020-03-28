#include "testingrecipestorage.h"

std::vector<Recipe> TestingRecipeStorage::read(time_t &maxId) const
{
    maxId = 0;
    return m_recipes;
}

bool TestingRecipeStorage::save(std::vector<Recipe> recipes, time_t maxId) const
{
    m_recipes = recipes;
    return true;
}

void TestingRecipeStorage::reset()
{
    m_recipes.clear();
}

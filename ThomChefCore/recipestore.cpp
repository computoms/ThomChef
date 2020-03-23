#include "recipestore.h"

RecipeStore::RecipeStore(std::shared_ptr<FileRecipeStorage> storage):
    m_storage   (storage)
{

}

void RecipeStore::initialize()
{
    m_recipes = m_storage->read();
}

int RecipeStore::getNumberOfRecipes() const
{
    if (!m_filter)
        return m_recipes.size();
    return m_filteredRecipeIndexes.size();
}

Recipe RecipeStore::getRecipe(int recipeIndex) const
{
    if (!m_filter)
    {
        if (recipeIndex < 0 || recipeIndex >= (int)m_recipes.size())
            throw std::invalid_argument("Recipe of index " + std::to_string(recipeIndex) + " not found");
        return m_recipes[recipeIndex];
    }

    if (recipeIndex < 0 || recipeIndex >= (int) m_filteredRecipeIndexes.size())
        throw std::invalid_argument("Recipe of index " + std::to_string(recipeIndex) + " not found with this filter.");
    if (m_filteredRecipeIndexes[recipeIndex] < 0 || m_filteredRecipeIndexes[recipeIndex] >= (int) m_recipes.size())
        throw std::invalid_argument("Recipe of index " + std::to_string(m_filteredRecipeIndexes[recipeIndex]) + " not found.");
    return m_recipes[m_filteredRecipeIndexes[recipeIndex]];
}

Recipe RecipeStore::findRecipeByName(std::string name) const
{
    for (auto &recipe : m_recipes)
        if (recipe.getName() == name)
            return recipe;
    throw std::invalid_argument("Could not find recipe with name " + name);
}

void RecipeStore::addRecipe(Recipe recipe)
{
    m_recipes.push_back(recipe);
    m_storage->save(m_recipes);
    emit changed();
}

void RecipeStore::deleteRecipe(Recipe recipe)
{
    for (auto it = m_recipes.begin(); it != m_recipes.end(); ++it)
    {
        if (it->getName() == recipe.getName())
        {
            m_recipes.erase(it);
            break;
        }
    }
    m_storage->save(m_recipes);
    emit changed();
}

void RecipeStore::setFilter(std::shared_ptr<Filter> filter)
{
    m_filter = filter;

    // Update filtered recipes
    m_filteredRecipeIndexes.clear();
    for (int i = 0; i < (int)m_recipes.size(); ++i)
    {
        if (m_filter->isInFilter(m_recipes[i]))
            m_filteredRecipeIndexes.push_back(i);
    }
}

void RecipeStore::removeFilter()
{
    m_filter.reset();
    m_filteredRecipeIndexes.clear();
}

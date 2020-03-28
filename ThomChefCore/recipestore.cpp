#include "recipestore.h"

RecipeStore::RecipeStore(RecipeStorage *storage):
    m_maxId     (0),
    m_storage   (storage)
{

}

void RecipeStore::initialize()
{
    m_recipes = m_storage->read(m_maxId);
    m_filters.clear();
}

time_t RecipeStore::newId()
{
    return ++m_maxId;
}

int RecipeStore::getNumberOfRecipes() const
{
    if (!hasFilter())
        return m_recipes.size();
    return m_filteredRecipeIndexes.size();
}

Recipe RecipeStore::getRecipe(int recipeIndex) const
{
    if (!hasFilter())
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

Recipe RecipeStore::findRecipe(long id) const
{
    for (auto &recipe : m_recipes)
        if (recipe.getId() == id)
            return recipe;
    throw std::invalid_argument("Could not find recipe of id " + std::to_string(id));
}

void RecipeStore::addRecipe(Recipe recipe)
{
    if (recipe.getId() > m_maxId)
        m_maxId = recipe.getId();
    m_recipes.push_back(recipe);
    m_storage->save(m_recipes, m_maxId);
    emit changed();
}

bool RecipeStore::updateRecipe(Recipe recipe)
{
    for (size_t i = 0; i < m_recipes.size(); ++i)
    {
        if (m_recipes[i].getId() == recipe.getId())
        {
            m_recipes[i] = recipe;
            m_storage->save(m_recipes, m_maxId);
            emit changed();
            return true;
        }
    }
    return false;
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
    m_storage->save(m_recipes, m_maxId);
    emit changed();
}

bool RecipeStore::hasFilter() const
{
    return m_filters.size() > 0;
}

bool RecipeStore::hasFilter(Filter *filter) const
{
    return std::find(m_filters.begin(), m_filters.end(), filter) != m_filters.end();
}

void RecipeStore::addFilter(Filter *filter)
{
    if (hasFilter(filter))
        return;
    if (filter == nullptr)
        return;

    m_filters.push_back(filter);
    connect(filter, SIGNAL(updated()), this, SLOT(on_filter_updated()));

    updateFilters();
}

void RecipeStore::removeFilter(Filter *filter)
{
    if (!hasFilter(filter))
        return;
    auto it = std::find(m_filters.begin(), m_filters.end(), filter);
    m_filters.erase(it);
    m_filteredRecipeIndexes.clear();

    updateFilters();
}

void RecipeStore::on_filter_updated()
{
    updateFilters();
}

void RecipeStore::updateFilters()
{
    m_filteredRecipeIndexes.clear();

    if (hasFilter())
    {
        for (int i = 0; i < (int)m_recipes.size(); ++i)
        {
            if (isInAllFilters(m_recipes[i]))
                m_filteredRecipeIndexes.push_back(i);
        }
    }

    emit changed();
}

bool RecipeStore::isInAllFilters(const Recipe &recipe) const
{
    for (auto &f : m_filters)
        if (!f->isInFilter(recipe))
            return false;
    return true;
}

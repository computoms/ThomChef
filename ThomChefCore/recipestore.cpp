#include "recipestore.h"

RecipeStore::RecipeStore(RecipeStorage *storage):
    m_storage   (storage),
    m_filter    (nullptr)
{

}

void RecipeStore::initialize()
{
    m_recipes = m_storage->read();
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
    m_recipes.push_back(recipe);
    m_storage->save(m_recipes);
    emit changed();
}

bool RecipeStore::updateRecipe(Recipe recipe)
{
    for (size_t i = 0; i < m_recipes.size(); ++i)
    {
        if (m_recipes[i].getId() == recipe.getId())
        {
            m_recipes[i] = recipe;
            m_storage->save(m_recipes);
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
    m_storage->save(m_recipes);
    emit changed();
}

bool RecipeStore::hasFilter() const
{
    return m_filter != nullptr;
}

void RecipeStore::setFilter(IngredientFilter *filter)
{
    m_filter = filter;
    if (m_filter)
        connect(m_filter, SIGNAL(updated()), this, SLOT(on_filter_updated()));

    updateFilter();
    emit changed();
}

void RecipeStore::removeFilter()
{
    m_filter = nullptr;
    m_filteredRecipeIndexes.clear();
}

void RecipeStore::on_filter_updated()
{
    updateFilter();
    emit changed();
}

void RecipeStore::updateFilter()
{
    if (!hasFilter())
        return;

    m_filteredRecipeIndexes.clear();
    for (int i = 0; i < (int)m_recipes.size(); ++i)
    {
        if (m_filter->isInFilter(m_recipes[i]))
            m_filteredRecipeIndexes.push_back(i);
    }
}

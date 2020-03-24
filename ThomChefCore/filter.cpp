#include "filter.h"

Filter::Filter()
{

}

bool Filter::isInFilter(Recipe &recipe) const
{
    for (auto &filterIngredient : m_ingredientFilters)
        if (!hasFilter(filterIngredient, recipe))
            return false;

    return true;
}

void Filter::addIngredientFilter(std::string ingredientFilter)
{
    m_ingredientFilters.push_back(ingredientFilter);
    emit updated();
}

void Filter::removeIngredientFilter(std::string ingredientFilter)
{
    for (auto it = m_ingredientFilters.begin(); it != m_ingredientFilters.end(); ++it)
    {
        if (*it == ingredientFilter)
        {
            m_ingredientFilters.erase(it);
            break;
        }
    }
    emit updated();
}

bool Filter::isEmpty() const
{
    return m_ingredientFilters.empty();
}

bool Filter::hasFilter(std::string ingredientFilter, Recipe &recipe) const
{
    int nbOfIngredients = recipe.getNumberOfIngredients();
    for (int j = 0; j < nbOfIngredients; ++j)
        if (filter(ingredientFilter, recipe.getIngredient(j)))
            return true;

    return false;
}

bool Filter::filter(std::string ingredientFilter, Ingredient ingredient) const
{
    return ingredient.getName().find(ingredientFilter) != std::string::npos;
}

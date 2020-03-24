#include "filter.h"

Filter::Filter()
{

}

bool Filter::isInFilter(Recipe &recipe) const
{
    for (int i = 0; i < recipe.getNumberOfIngredients(); ++i)
        if (!isInFilter(recipe.getIngredient(i)))
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

bool Filter::isInFilter(Ingredient ingredient) const
{
    for (auto &f : m_ingredientFilters)
        if (this->match(f, ingredient))
            return true;
    return false;
}

bool Filter::match(std::string ingredientFilter, Ingredient ingredient) const
{
    return ingredient.getName().find(ingredientFilter) != std::string::npos;
}

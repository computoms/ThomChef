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

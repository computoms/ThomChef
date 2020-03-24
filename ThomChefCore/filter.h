#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include "recipe.h"

class Filter
{
public:
    Filter();

    bool isInFilter(Recipe &recipe) const;
    void addIngredientFilter(std::string ingredientFilter);

private:
    bool hasFilter(std::string ingredientFilter, Recipe &recipe) const;
    bool filter(std::string ingredientFilter, Ingredient ingredient) const;

private:
    std::vector<std::string> m_ingredientFilters;
};

#endif // FILTER_H

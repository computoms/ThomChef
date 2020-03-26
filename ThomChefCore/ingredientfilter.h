#ifndef INGREDIENTFILTER_H
#define INGREDIENTFILTER_H

#include <vector>
#include "filter.h"
#include "recipe.h"

class IngredientFilter : public Filter
{

public:
    IngredientFilter();

    virtual bool isInFilter(const Recipe &recipe) const override;
    void addIngredientFilter(std::string ingredientFilter);
    void removeIngredientFilter(std::string ingredientFilter);
    bool isEmpty() const;

    void setDefaultIngredients(std::vector<std::string> defaultIngredients);

private:
    bool isInFilter(Ingredient ingredient) const;
    bool match(std::string ingredientFilter, Ingredient ingredient) const;

private:
    std::vector<std::string> m_ingredientFilters;
    std::vector<std::string> m_defaultIngredientFilters;
};

#endif // INGREDIENTFILTER_H

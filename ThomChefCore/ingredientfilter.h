#ifndef INGREDIENTFILTER_H
#define INGREDIENTFILTER_H

#include <vector>
#include "filter.h"
#include "recipe.h"

/**
 * @brief The IngredientFilter class filters Recipe(s) by ingredients, when
 * added to the RecipeStore filters.
 */
class IngredientFilter : public Filter
{

public:
    IngredientFilter();

    virtual bool isInFilter(const Recipe &recipe) const override;
    bool addIngredientFilter(std::string ingredientFilter);
    void removeIngredientFilter(std::string ingredientFilter);
    bool isEmpty() const;

    void setDefaultIngredients(std::vector<std::string> defaultIngredients);

private:
    bool isInFilter(Ingredient ingredient) const;
    bool match(std::string ingredientFilter, Ingredient ingredient) const;
    bool containsFilter(std::string filter) const;

private:
    std::vector<std::string> m_ingredientFilters;
    std::vector<std::string> m_defaultIngredientFilters;
};

#endif // INGREDIENTFILTER_H

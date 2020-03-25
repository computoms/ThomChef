#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include "recipe.h"
#include <QObject>

class IngredientFilter : public QObject
{
    Q_OBJECT

public:
    IngredientFilter();

    bool isInFilter(Recipe &recipe) const;
    void addIngredientFilter(std::string ingredientFilter);
    void removeIngredientFilter(std::string ingredientFilter);
    bool isEmpty() const;

    void setDefaultIngredients(std::vector<std::string> defaultIngredients);

signals:
    void updated();

private:
    bool isInFilter(Ingredient ingredient) const;
    bool match(std::string ingredientFilter, Ingredient ingredient) const;

private:
    std::vector<std::string> m_ingredientFilters;
    std::vector<std::string> m_defaultIngredientFilters;
};

#endif // FILTER_H

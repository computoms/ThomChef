#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include "recipe.h"
#include <QObject>

class Filter : public QObject
{
    Q_OBJECT

public:
    Filter();

    bool isInFilter(Recipe &recipe) const;
    void addIngredientFilter(std::string ingredientFilter);
    void removeIngredientFilter(std::string ingredientFilter);
    bool isEmpty() const;

signals:
    void updated();

private:
    bool hasFilter(std::string ingredientFilter, Recipe &recipe) const;
    bool filter(std::string ingredientFilter, Ingredient ingredient) const;

private:
    std::vector<std::string> m_ingredientFilters;
};

#endif // FILTER_H

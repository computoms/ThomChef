#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include "recipe.h"

/**
 * @brief The Filter class represents a Recipe's filter.
 * It is an abstract class that defines the interface of a filter.
 * Filter(s) can be added to the RecipeStore to filter the recipes.
 */
class Filter : public QObject
{
    Q_OBJECT
public:
    Filter();

    virtual bool isInFilter(const Recipe &recipe) const = 0;

protected:
    void filterUpdated();

signals:
    void updated();
};

#endif // FILTER_H

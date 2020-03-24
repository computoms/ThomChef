#ifndef FILTERTESTS_H
#define FILTERTESTS_H

#include <QtTest>
#include "filter.h"


class FilterTests: public QObject
{
    Q_OBJECT

public:
    FilterTests();

private slots:
    void initTestCase();

    void isInFilter_recipeWithFilterIngredient_ReturnsTrue();
    void isInFilter_recipeWithDifferentIngredient_ReturnsFalse();
    void isInFilter_recipeWithPartialFilter_ReturnsTrue();

private:
    Recipe m_recipe;
};

#endif // FILTERTESTS_H

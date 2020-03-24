#include "filtertests.h"

FilterTests::FilterTests():
    m_recipe    ("TestRecipe", Category_Quick, "", 0)
{

}

void FilterTests::initTestCase()
{
    qDebug("Init called");
    m_recipe = Recipe("TestRecipe", Category_Quick, "", 0);
    m_recipe.addIngredient(Ingredient("Tomato", 1, UnitType_Number));
}

void FilterTests::isInFilter_recipeWithFilterIngredient_ReturnsTrue()
{
    Filter filter;
    filter.addIngredientFilter("Tomato");

    bool result = filter.isInFilter(m_recipe);

    QCOMPARE(result, true);
}

void FilterTests::isInFilter_recipeWithDifferentIngredient_ReturnsFalse()
{
    Filter filter;
    filter.addIngredientFilter("Carotte");

    bool result = filter.isInFilter(m_recipe);

    QCOMPARE(result, false);
}

void FilterTests::isInFilter_recipeWithPartialFilter_ReturnsTrue()
{
    Filter filter;
    filter.addIngredientFilter("Toma");

    bool result = filter.isInFilter(m_recipe);

    QCOMPARE(result, true);
}

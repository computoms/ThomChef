#ifndef RANDOMRECIPESELECTORTESTS_H
#define RANDOMRECIPESELECTORTESTS_H

#include <QtTest>
#include "testingrecipestorage.h"
#include "ThomChefCore/randomrecipeselector.h"

class RandomRecipeSelectorTests: public QObject
{
    Q_OBJECT
public:
    RandomRecipeSelectorTests();

private slots:
    void getListOfIngredients_WithTwoIdenticalIngredients_ReturnsOnlyOneIngredient();
    void getListOfIngredients_WithTwoIngredientsWithDifferentUnits_ReturnsTwoIngredients();

    void addRecipeWithOneIngredient_EmptyStore_ReturnsOneIngredient();
    void removeRecipeWithOneIngredient_StoreContainingOneRecipesWithSingleIngredients_ReturnsZeroIngredient();

private:
    void createSimpleSelector();

    TestingRecipeStorage storage;
    RecipeStore store;
    RandomRecipeSelector selector;
};

#endif // RANDOMRECIPESELECTORTESTS_H

#include "randomrecipeselectortests.h"
#include "ThomChefCore/recipestore.h"


RandomRecipeSelectorTests::RandomRecipeSelectorTests():
    store       (&storage),
    selector    (&store)
{

}

void RandomRecipeSelectorTests::getListOfIngredients_WithTwoIdenticalIngredients_ReturnsOnlyOneIngredient()
{
    createSimpleSelector();
    Recipe recipe("Test", 1, "", 0);
    recipe.addIngredient(Ingredient("Eggs", 2, UnitTypes().Number));
    recipe.addIngredient(Ingredient("Eggs", 3, UnitTypes().Number));
    store.addRecipe(recipe);

    selector.selectRecipes(1);
    auto ingredientList = selector.getListOfIngredients();

    QCOMPARE((int) ingredientList.size(), 1);
    QCOMPARE(ingredientList[0].getName(), "Eggs");
    QCOMPARE(ingredientList[0].getQuantity(), 5.0);
}

void RandomRecipeSelectorTests::getListOfIngredients_WithTwoIngredientsWithDifferentUnits_ReturnsTwoIngredients()
{
    createSimpleSelector();
    Recipe recipe("Test", 1, "", 0);
    recipe.addIngredient(Ingredient("Flour", 200, UnitTypes().Grammes));
    recipe.addIngredient(Ingredient("Flour", 1, UnitTypes().Cup));
    store.addRecipe(recipe);

    selector.selectRecipes(1);
    auto ingredientList = selector.getListOfIngredients();

    QCOMPARE((int) ingredientList.size(), 2);
    QCOMPARE(ingredientList[0].getName(), "Flour");
    QCOMPARE(ingredientList[1].getName(), "Flour");
}

void RandomRecipeSelectorTests::createSimpleSelector()
{
    storage.reset();
    store.initialize();
}

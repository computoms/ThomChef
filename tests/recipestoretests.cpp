#include "recipestoretests.h"
#include "recipe.h"
#include <iostream>

std::vector<Recipe> TestingRecipeStorage::read() const
{
    return m_recipes;
}

bool TestingRecipeStorage::save(std::vector<Recipe> recipes) const
{
    m_recipes = recipes;
    return true;
}

void TestingRecipeStorage::reset()
{
    m_recipes.clear();
}


RecipeStoreTests::RecipeStoreTests():
    storage(std::make_shared<TestingRecipeStorage>()),
    store(storage),
    recipe1(1, "Test1", Category_Quick, "", 5),
    recipe2(2, "Test2", Category_Standard, "", 10)
{
}

void RecipeStoreTests::add_twoRecipesToEmptyStore_addsRecipeToStore()
{
    init();

    QCOMPARE(storage->m_recipes.size(), 2);
    QCOMPARE(storage->m_recipes[0].getId(), 1);
}

void RecipeStoreTests::update_storeContainingSingleRecipe_UpdatesRecipe()
{
    init();

    Recipe updatedRecipe(1, "Test2", Category_Quick, "This is a description", 25);
    store.updateRecipe(updatedRecipe);

    QCOMPARE(storage->m_recipes[0].getId(), 1);
    QCOMPARE(storage->m_recipes[0].getName(), "Test2");
    QCOMPARE(storage->m_recipes[0].getDescription(), "This is a description");
    QCOMPARE(storage->m_recipes[0].getPreparationTimeInMinutes(), 25);
}

void RecipeStoreTests::delete_storeContainingTwoRecipes_containsOnlyOneRecipe()
{
    init();

    store.deleteRecipe(recipe2);

    QVERIFY_EXCEPTION_THROWN(store.findRecipeByName("Test2"), std::invalid_argument);
}

void RecipeStoreTests::generateUniqueId_Implementation_Test()
{
    auto now = std::chrono::system_clock::now();
    time_t nowTt = std::chrono::system_clock::to_time_t(now);
    time_t reference = 1577836800;
    QVERIFY(nowTt - reference < 10000000);
}

void RecipeStoreTests::find_storeContainingTwoRecipes_findsCorrectRecipe()
{
    init();

    Recipe r = store.findRecipe(2);
    QCOMPARE(r.getId(), 2);
}

void RecipeStoreTests::setFilter_withFilterThatRestrictsStoreToOneRecipe_ReturnsOnlyOneRecipe()
{
    init();

    recipe1.addIngredient(Ingredient("Tomato", 1, UnitType_Number));
    store.updateRecipe(recipe1);

    QCOMPARE(store.getNumberOfRecipes(), 2);

    std::shared_ptr<Filter> filter = std::make_shared<Filter>();
    filter->addIngredientFilter("Tomato");
    store.setFilter(filter);

    QCOMPARE(store.getNumberOfRecipes(), 1);
}

void RecipeStoreTests::setFilter_partialFilter_SelectsCorrectRecipes()
{
    init();

    recipe1.addIngredient(Ingredient("Tomato", 1, UnitType_Number));

    std::shared_ptr<Filter> filter = std::make_shared<Filter>();
    filter->addIngredientFilter("Toma");
    store.setFilter(filter);

    QCOMPARE(store.getNumberOfRecipes(), 1);
}

void RecipeStoreTests::init()
{
    storage->reset();
    store.initialize();
    store.addRecipe(recipe1);
    store.addRecipe(recipe2);
}


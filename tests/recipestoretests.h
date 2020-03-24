#ifndef RECIPESTORETESTS_H
#define RECIPESTORETESTS_H
#include <QtTest>

#include "ThomChefCore/filerecipestorage.h"
#include "ThomChefCore/recipestore.h"

class TestingRecipeStorage : public RecipeStorage
{
public:
    virtual std::vector<Recipe> read() const override;
    virtual bool save(std::vector<Recipe> recipes) const override;

    void reset();

    mutable std::vector<Recipe> m_recipes;
};

class RecipeStoreTests : public QObject
{
    Q_OBJECT

public:
    RecipeStoreTests();

private slots:
    void add_twoRecipesToEmptyStore_addsRecipeToStore();
    void update_storeContainingSingleRecipe_UpdatesRecipe();
    void delete_storeContainingTwoRecipes_containsOnlyOneRecipe();
    void generateUniqueId_Implementation_Test();
    void find_storeContainingTwoRecipes_findsCorrectRecipe();
    void setFilter_withFilterThatRestrictsStoreToOneRecipe_ReturnsOnlyOneRecipe();
    void setFilter_partialFilter_SelectsCorrectRecipes();

private:
    void init();
    std::shared_ptr<TestingRecipeStorage> storage;
    RecipeStore store;
    Recipe recipe1;
    Recipe recipe2;
};

#endif // RECIPESTORETESTS_H

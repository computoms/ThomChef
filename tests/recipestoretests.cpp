#include "recipestoretests.h"
#include "recipestore.h"
#include "recipe.h"

RecipeStoreTests::RecipeStoreTests()
{

}

void RecipeStoreTests::delete_storeContainingTwoRecipes_containsOnlyOneRecipe()
{
    std::shared_ptr<FileRecipeStorage> storage = std::make_shared<FileRecipeStorage>("test.xml");
    RecipeStore store(storage);
    store.addRecipe(Recipe("Test1", Category_Quick, "", 5));
    Recipe recipeToDelete = Recipe("Test2", Category_Quick, "", 5);
    store.addRecipe(recipeToDelete);

    store.deleteRecipe(recipeToDelete);

    QVERIFY_EXCEPTION_THROWN(store.findRecipeByName("Test2"), std::invalid_argument);
}

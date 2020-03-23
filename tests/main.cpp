#include <QtTest>
#include "recipestoragetests.h"
#include "recipestoretests.h"

int main(int argc, char *argv[])
{
    int status = 0;

    RecipeStorageTests recipeStorageTests;
    status |= QTest::qExec(&recipeStorageTests, argc, argv);

    RecipeStoreTests recipeStoreTests;
    status |= QTest::qExec(&recipeStoreTests, argc, argv);

    return status;
}

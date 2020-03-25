#include <QtTest>
#include "recipestoragetests.h"
#include "recipestoretests.h"
#include "filtertests.h"
#include "configurationstoragetests.h"

int main(int argc, char *argv[])
{
    int status = 0;

    RecipeStorageTests recipeStorageTests;
    status |= QTest::qExec(&recipeStorageTests, argc, argv);

    RecipeStoreTests recipeStoreTests;
    status |= QTest::qExec(&recipeStoreTests, argc, argv);

    FilterTests filterTests;
    status |= QTest::qExec(&filterTests, argc, argv);

    ConfigurationStorageTests configStorageTests;
    status |= QTest::qExec(&configStorageTests, argc, argv);

    return status;
}

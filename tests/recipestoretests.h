#ifndef RECIPESTORETESTS_H
#define RECIPESTORETESTS_H
#include <QtTest>

class RecipeStoreTests : public QObject
{
    Q_OBJECT

public:
    RecipeStoreTests();

private slots:
    void delete_storeContainingTwoRecipes_containsOnlyOneRecipe();
};

#endif // RECIPESTORETESTS_H

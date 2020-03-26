#ifndef TESTINGRECIPESTORAGE_H
#define TESTINGRECIPESTORAGE_H

#include "ThomChefCore/Storage/recipestorage.h"

class TestingRecipeStorage : public RecipeStorage
{
public:
    TestingRecipeStorage() {}
    virtual ~TestingRecipeStorage() {}

    virtual std::vector<Recipe> read() const override;
    virtual bool save(std::vector<Recipe> recipes) const override;

    void reset();

    mutable std::vector<Recipe> m_recipes;
};
#endif // TESTINGRECIPESTORAGE_H

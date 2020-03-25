#ifndef RECIPESTORE_H
#define RECIPESTORE_H

#include <QObject>

#include "recipe.h"
#include <vector>
#include "filerecipestorage.h"
#include "ingredientfilter.h"

/**
 * @brief The RecipeStore class represents the database interface to the recipes.
 */
class RecipeStore : public QObject
{
    Q_OBJECT

public:
    RecipeStore(std::shared_ptr<RecipeStorage> storage);

    void initialize();

    int getNumberOfRecipes() const;
    Recipe getRecipe(int recipeIndex) const;
    Recipe findRecipeByName(std::string name) const;
    Recipe findRecipe(long id) const;

    void addRecipe(Recipe recipe);
    bool updateRecipe(Recipe recipe);
    void deleteRecipe(Recipe recipe);

    bool hasFilter() const;
    void setFilter(std::shared_ptr<IngredientFilter> filter);
    void removeFilter();

signals:
    void changed();

private slots:
    void on_filter_updated();

private:
    void updateFilter();

private:
    std::vector<Recipe> m_recipes;
    std::shared_ptr<RecipeStorage> m_storage;
    std::shared_ptr<IngredientFilter> m_filter;
    std::vector<int> m_filteredRecipeIndexes;

};

#endif // RECIPESTORE_H

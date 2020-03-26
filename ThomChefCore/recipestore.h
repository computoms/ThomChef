#ifndef RECIPESTORE_H
#define RECIPESTORE_H

#include <QObject>

#include "recipe.h"
#include <vector>
#include "Storage/recipestorage.h"
#include "ingredientfilter.h"

/**
 * @brief The RecipeStore class represents the database interface to the recipes.
 */
class RecipeStore : public QObject
{
    Q_OBJECT

public:
    RecipeStore(RecipeStorage *storage);

    void initialize();

    int getNumberOfRecipes() const;
    Recipe getRecipe(int recipeIndex) const;
    Recipe findRecipeByName(std::string name) const;
    Recipe findRecipe(long id) const;

    void addRecipe(Recipe recipe);
    bool updateRecipe(Recipe recipe);
    void deleteRecipe(Recipe recipe);

    bool hasFilter() const;
    bool hasFilter(Filter *filter) const;
    void addFilter(Filter *filter);
    void removeFilter(Filter *filter);

signals:
    void changed();

private slots:
    void on_filter_updated();

private:
    void updateFilters();
    bool isInAllFilters(const Recipe &recipe) const;

private:
    std::vector<Recipe> m_recipes;
    RecipeStorage *m_storage;
    std::vector<Filter *> m_filters;
    std::vector<int> m_filteredRecipeIndexes;

};

#endif // RECIPESTORE_H

#ifndef RECIPESTORE_H
#define RECIPESTORE_H

#include <QObject>

#include "recipe.h"
#include <vector>
#include "filerecipestorage.h"
#include "filter.h"

class RecipeStore : public QObject
{
    Q_OBJECT

public:
    RecipeStore(std::shared_ptr<FileRecipeStorage> storage);

    void initialize();

    int getNumberOfRecipes() const;
    Recipe getRecipe(int recipeIndex) const;
    Recipe findRecipeByName(std::string name) const;

    void addRecipe(Recipe recipe);
    void deleteRecipe(Recipe recipe);

    void setFilter(std::shared_ptr<Filter> filter);
    void removeFilter();

signals:
    void changed();

private:
    std::vector<Recipe> m_recipes;
    std::shared_ptr<FileRecipeStorage> m_storage;
    std::shared_ptr<Filter> m_filter;
    std::vector<int> m_filteredRecipeIndexes;

};

#endif // RECIPESTORE_H

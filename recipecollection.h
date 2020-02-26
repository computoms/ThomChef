#ifndef RECETTECOLLECTION_H
#define RECETTECOLLECTION_H

#include "recette.h"


class RecipeCollection
{
public:
    RecipeCollection();

    int getNumberOfRecipes() const;
    Recette getRecipe(int recipeIndex) const;

    void addRecipe(Recette recette);

private:
    std::vector<Recette> recipes;
};

#endif // RECETTECOLLECTION_H

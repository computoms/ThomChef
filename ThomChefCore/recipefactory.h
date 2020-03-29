#ifndef RECIPEFACTORY_H
#define RECIPEFACTORY_H
#include "recipestore.h"

/**
 * @brief The RecipeFactory class manages the creation of Recipe instances.
 * It manages the Recipe ids from the RecipeStore.
 */
class RecipeFactory
{
public:
    RecipeFactory(RecipeStore *store);

    Recipe createRecipe(std::string name, int numberOFPersons, std::string description, double preparationTimeInMinutes);

private:
    RecipeStore *m_store;
};

#endif // RECIPEFACTORY_H

#include "recipefactory.h"

RecipeFactory::RecipeFactory(RecipeStore *store):
    m_store (store)
{

}

Recipe RecipeFactory::createRecipe(std::string name, int numberOFPersons, std::string description, double preparationTimeInMinutes)
{
    return Recipe(m_store->newId(), name, numberOFPersons, description, preparationTimeInMinutes);
}




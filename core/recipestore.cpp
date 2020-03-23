#include "recipestore.h"

RecipeStore::RecipeStore(std::shared_ptr<FileRecipeStorage> storage):
    m_storage   (storage)
{

}

void RecipeStore::initialize()
{
    m_recipes = m_storage->read();
}

int RecipeStore::getNumberOfRecipes() const
{
    return m_recipes.size();
}

Recipe RecipeStore::getRecipe(int recipeIndex) const
{
    if (recipeIndex < 0 || recipeIndex >= (int)m_recipes.size())
        throw std::invalid_argument("Recipe of index " + std::to_string(recipeIndex) + " not found");
    return m_recipes[recipeIndex];
}

Recipe RecipeStore::findRecipeByName(std::string name) const
{
    for (auto &recipe : m_recipes)
        if (recipe.getName() == name)
            return recipe;
    throw std::invalid_argument("Could not find recipe with name " + name);
}

void RecipeStore::addRecipe(Recipe recette)
{
    m_recipes.push_back(recette);
    m_storage->save(m_recipes);
}

#include "filerecipestorage.h"
#include "conversions.h"
#include <sstream>

using namespace pugi;

FileRecipeStorage::FileRecipeStorage(std::string filename):
    m_filename  (filename)
{

}

Recipe FileRecipeStorage::readRecipe(std::string recipeSerialization)
{
    xml_document doc;
    xml_parse_result result = doc.load_string(recipeSerialization.c_str());
    if (!result)
        throw std::ios_base::failure("Could not read the RecipeStore file");

    xml_node recipeNode = doc.first_child();
    std::string name = recipeNode.child("Name").child_value();
    std::string category = recipeNode.child("Category").child_value();
    std::string description = recipeNode.child("Description").child_value();
    std::string prepTime = recipeNode.child("PreparationTime").child_value();

    Recipe recipe(name, Conversions::to_category(category), description, Conversions::to_double(prepTime));
    for (pugi::xml_node ingNode = recipeNode.child("Ingredients").child("Ingredient");
             ingNode; ingNode = ingNode.next_sibling("Ingredient"))
    {
        std::string ingName = ingNode.child("Name").child_value();
        std::string quantity = ingNode.child("Quantity").child_value();
        std::string unit = ingNode.child("Unit").child_value();

        Ingredient ing(ingName, Conversions::to_double(quantity), Conversions::to_unitType(unit));
        recipe.addIngredient(ing);
    }

    return recipe;
}

std::string FileRecipeStorage::serializeRecipe(Recipe recipe)
{
    pugi::xml_document doc;
    pugi::xml_node recipeNode = doc.append_child("Recipe");
    recipeNode.append_child("Name").append_child(pugi::node_pcdata).set_value(recipe.getName().c_str());
    recipeNode.append_child("Category").append_child(pugi::node_pcdata).set_value(Conversions::to_string(recipe.getCategory()).c_str());
    recipeNode.append_child("Description").append_child(pugi::node_pcdata).set_value(recipe.getDescription().c_str());
    recipeNode.append_child("PreparationTime").append_child(pugi::node_pcdata).set_value(std::to_string(recipe.getPreparationTimeInMinutes()).c_str());
    pugi::xml_node ingredientCollectionNode = recipeNode.append_child("Ingredients");

    int numberOfIngredients = recipe.getNumberOfIngredients();
    for (int i = 0; i < numberOfIngredients; ++i)
    {
        Ingredient ing = recipe.getIngredient(i);
        pugi::xml_node ingNode = ingredientCollectionNode.append_child("Ingredient");
        ingNode.append_child("Name").append_child(pugi::node_pcdata).set_value(ing.getName().c_str());
        ingNode.append_child("Quantity").append_child(pugi::node_pcdata).set_value(std::to_string(ing.getQuantity()).c_str());
        ingNode.append_child("Unit").append_child(pugi::node_pcdata).set_value(Conversions::to_string(ing.getUnit()).c_str());
    }

    std::stringstream ss;
    doc.save(ss);

    return ss.str();
}

std::vector<Recipe> FileRecipeStorage::read()
{
    pugi::xml_document doc;
    xml_parse_result result = doc.load_file(m_filename.c_str());
    if (!result)
        throw std::ios_base::failure("Could not read the RecipeStore file");

    std::vector<Recipe> recipes;
    for (xml_node recipeNode = doc.child("RecipeStore").child("Recipe");
         recipeNode; recipeNode = recipeNode.next_sibling("Recipe"))
    {
        std::stringstream ss;
        recipeNode.print(ss);
        Recipe recipe = readRecipe(ss.str());
        recipes.push_back(recipe);
    }
    return recipes;
}

bool FileRecipeStorage::save(std::vector<Recipe> recipes)
{
    xml_document doc;
    xml_node recipeStoreNode = doc.append_child("RecipeStore");
    for (int i(0); i < recipes.size(); ++i)
    {
        Recipe recipe = recipes[i];
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(serializeRecipe(recipe).c_str());
        if (!result)
            throw std::ios_base::failure("Could not read the RecipeStore file");
        recipeStoreNode.append_copy(doc.first_child());
    }
    return doc.save_file(m_filename.c_str());
}

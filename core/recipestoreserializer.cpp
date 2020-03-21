#include "recipestoreserializer.h"
#include "conversions.h"
#include <sstream>

using namespace pugi;

RecipeStoreSerializer::RecipeStoreSerializer()
{

}

Recipe RecipeStoreSerializer::readRecipe(std::string recipeSerialization)
{
    xml_document doc;
    xml_parse_result result = doc.load_string(recipeSerialization.c_str()); // TODO Handle errors
    xml_node recipeNode = doc.root();
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

std::string RecipeStoreSerializer::serializeRecipe(Recipe recipe)
{
    pugi::xml_document doc;
    pugi::xml_node recipeNode = doc.root();
    recipeNode.set_name("Recipe");
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

RecipeStore RecipeStoreSerializer::read(std::string filename)
{
    pugi::xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    if (!result)
        return RecipeStore(); // Handle error

    RecipeStore recipeStore;
    for (xml_node recipeNode = doc.child("RecipeStore").child("Recipe");
         recipeNode; recipeNode = recipeNode.next_sibling("Recipe"))
    {
        std::stringstream ss;
        recipeNode.print(ss);
        Recipe recipe = readRecipe(ss.str());
        recipeStore.addRecipe(recipe);
    }
    return recipeStore;
}

bool RecipeStoreSerializer::serializeTo(std::string filename, RecipeStore recipeStore)
{
    xml_document doc;
    xml_node recipeStoreNode = doc.append_child("RecipeStore");
    for (int i(0); i < recipeStore.getNumberOfRecipes(); ++i)
    {
        Recipe recipe = recipeStore.getRecipe(i);
        pugi::xml_document doc;
        doc.load(serializeRecipe(recipe).c_str()); // TODO Handle errors // TODO Deprecated
        recipeStoreNode.append_copy(doc.root());
    }
    return doc.save_file(filename.c_str());
}

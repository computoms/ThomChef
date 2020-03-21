#include "libs/catch/catch.hpp"

#include "core/recipestoreserializer.h"
#include <sstream>

TEST_CASE("SerializeRecipe_ValidXmlNode_ReturnsValidRecipe")
{
    RecipeStoreSerializer serializer;
    Recipe probingRecipe("My Testing Recipe", Category_Quick, "This is my description", 45);
    probingRecipe.addIngredient(Ingredient("Eggs", 2, UnitType_Number));
    probingRecipe.addIngredient(Ingredient("Cream", 20, UnitType_Mililiters));
    probingRecipe.addIngredient(Ingredient("Cheese", 2, UnitType_Cup));


    std::string serialization = serializer.serializeRecipe(probingRecipe);



    pugi::xml_document doc;
    doc.load(serialization.c_str());

    std::string name = doc.root().child_value("Name");
    std::string category = doc.root().child_value("Category");
    std::string desc = doc.root().child_value("Description");
    std::string time = doc.root().child_value("PreparationTime");

    REQUIRE(name == "My Testing Recipe");
    REQUIRE(category == "Category_Quick");
    REQUIRE(desc == "This is my description");
    REQUIRE(time == "45");
}

TEST_CASE("ReadRecipeSerialization_ValidXml_ReturnsValidRecipe")
{
    RecipeStoreSerializer serializer;
    pugi::xml_document doc;
    pugi::xml_node recipeNode = doc.root();
    recipeNode.set_name("Recipe");
    recipeNode.append_child("Name").append_child(pugi::node_pcdata).set_value("My Testing Recipe");
    recipeNode.append_child("Category").append_child(pugi::node_pcdata).set_value("Category_Quick");
    recipeNode.append_child("Description").append_child(pugi::node_pcdata).set_value("This is my description");
    recipeNode.append_child("PreparationTime").append_child(pugi::node_pcdata).set_value("45");
    pugi::xml_node ingredientCollectionNode = recipeNode.append_child("Ingredients");

    pugi::xml_node ingNode = ingredientCollectionNode.append_child("Ingredient");
    ingNode.append_child("Name").append_child(pugi::node_pcdata).set_value("Egg");
    ingNode.append_child("Quantity").append_child(pugi::node_pcdata).set_value("2");
    ingNode.append_child("Unit").append_child(pugi::node_pcdata).set_value("UnitType_Number");

    std::stringstream ss;
    doc.save(ss);

    Recipe recipe = serializer.readRecipe(ss.str());
    REQUIRE(recipe.getName() == "My Testing Recipe");
    REQUIRE(recipe.getCategory() == Category_Quick);
    REQUIRE(recipe.getDescription() == "This is my description");
    REQUIRE(recipe.getPreparationTimeInMinutes() == 45);
}

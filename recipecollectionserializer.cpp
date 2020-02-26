#include "recipecollectionserializer.h"
#include "conversions.h"

using namespace pugi;

RecipeCollectionSerializer::RecipeCollectionSerializer()
{

}

RecipeCollection RecipeCollectionSerializer::read(std::string filename)
{
    pugi::xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    if (!result)
        return RecipeCollection(); // Handle error

    RecipeCollection recipeCollection;
    for (xml_node recipeNode = doc.child("RecipeCollection").child("Recipe");
         recipeNode; recipeNode = recipeNode.next_sibling("Recipe"))
    {
        Recette recipe = readRecipe(recipeNode);
        recipeCollection.addRecipe(recipe);
    }
    return recipeCollection;
}

Recette RecipeCollectionSerializer::readRecipe(xml_node recipeNode)
{
    std::string name = recipeNode.child("Name").value();
    std::string time = recipeNode.child("Time").value();
    std::string category = recipeNode.child("Category").value();
    std::string freezeDate = recipeNode.child("CongelationDate").value();
    std::string description = recipeNode.child("Description").value();
    std::string numberOfMeals = recipeNode.child("NumberOfMeals").value();
    std::string isFrozen = recipeNode.child("IsFrozen").value();
    std::string shouldBeRemoved = recipeNode.child("ShouldBeRemoved").value();

    std::vector<std::string> ingredients;
    for (pugi::xml_node ingNode = recipeNode.child("Ingredients").child("Ingredient");
             ingNode; ingNode = ingNode.next_sibling("Ingredient"))
    {
        ingredients.push_back(ingNode.value());
    }

    Recette recipe(name, Conversions::to_int(category), description, ingredients, Conversions::to_bool(isFrozen));
    recipe.setTemps(Conversions::to_int(time));
    recipe.setDateCongel(freezeDate);
    recipe.setNombreRepas(Conversions::to_int(numberOfMeals));
    recipe.setARetirer(Conversions::to_bool(shouldBeRemoved));

    return recipe;
}

bool RecipeCollectionSerializer::serializeTo(string filename, RecipeCollection recipeCollection)
{
    xml_document doc;
    xml_node recipeCollectionNode = doc.append_child("RecipeCollection");
    for (int i(0); i < recipeCollection.getNumberOfRecipes(); ++i)
    {
        Recette recipe = recipeCollection.getRecipe(i);
        recipeCollectionNode.append_copy(serializeRecipe(recipe));
    }
    return doc.save_file(filename.c_str());
}

pugi::xml_node RecipeCollectionSerializer::serializeRecipe(Recette recipe)
{
    pugi::xml_node recipeNode;
    recipeNode.set_name("Recipe");
    recipeNode.append_child("Name").set_value(recipe.getNom().c_str());
    recipeNode.append_child("Time").set_value(std::to_string(recipe.getTemps()).c_str());
    recipeNode.append_child("Category").set_value(std::to_string(recipe.getCategorie()).c_str());
    recipeNode.append_child("CongelationDate").set_value(recipe.getDateCongel().c_str());
    recipeNode.append_child("Description").set_value(recipe.getDescription().c_str());
    recipeNode.append_child("NumberOfMeals").set_value(std::to_string(recipe.getNombreRepas()).c_str());
    recipeNode.append_child("IsFrozen").set_value(std::to_string(recipe.getCongel()).c_str());
    recipeNode.append_child("ShouldBeRemoved").set_value(std::to_string(recipe.getARetirer()).c_str());
    pugi::xml_node ingredientCollectionNode = recipeNode.append_child("Ingredients");

    for (auto &ing : recipe.getTableauIngredients())
        ingredientCollectionNode.append_child("Ingredient").set_value(ing.c_str());

    return recipeNode;
}

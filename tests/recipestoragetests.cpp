#include <sstream>
#include <fstream>
#include "recipestoragetests.h"
#include "libs/pugixml-1.9/src/pugixml.hpp"

RecipeStorageTests::RecipeStorageTests():
    m_storage("test.xml"),
    m_defaultFilename   ("test.xml")
{

}

RecipeStorageTests::~RecipeStorageTests()
{

}

void RecipeStorageTests::saveSimpleFileStorage()
{
    std::vector<Recipe> recipes;
    Recipe recipe(1, "Testing recipe", 1, "Description of the recipe.", 20);
    recipe.addIngredient(Ingredient("Tomato", 1, UnitTypes().Number));
    recipe.addIngredient(Ingredient("Egg", 2, UnitTypes().Number));
    recipes.push_back(recipe);

    m_storage.save(recipes, 0);
}

std::string RecipeStorageTests::serializeSimpleRecipe()
{
    Recipe probingRecipe(1, "My Testing Recipe", 1, "This is my description", 45);
    probingRecipe.addIngredient(Ingredient("Eggs", 2, UnitTypes().Number));
    probingRecipe.addIngredient(Ingredient("Cream", 20, UnitTypes().Mililiters));
    probingRecipe.addIngredient(Ingredient("Cheese", 2, UnitTypes().Cup));

    return m_storage.serializeRecipe(probingRecipe);
}

std::string RecipeStorageTests::generateSimpleRecipeSerialization()
{
    pugi::xml_document doc;
    pugi::xml_node recipeNode = doc.append_child("Recipe");
    recipeNode.append_child("Id").append_child(pugi::node_pcdata).set_value("1");
    recipeNode.append_child("Name").append_child(pugi::node_pcdata).set_value("My Testing Recipe");
    recipeNode.append_child("NumberOfPersons").append_child(pugi::node_pcdata).set_value("1");
    recipeNode.append_child("Description").append_child(pugi::node_pcdata).set_value("This is my description");
    recipeNode.append_child("PreparationTime").append_child(pugi::node_pcdata).set_value("45");
    pugi::xml_node ingredientCollectionNode = recipeNode.append_child("Ingredients");

    pugi::xml_node ingNode = ingredientCollectionNode.append_child("Ingredient");
    ingNode.append_child("Name").append_child(pugi::node_pcdata).set_value("Egg");
    ingNode.append_child("Quantity").append_child(pugi::node_pcdata).set_value("2");
    ingNode.append_child("Unit").append_child(pugi::node_pcdata).set_value("UnitType_Number");

    std::stringstream ss;
    doc.save(ss);
    return ss.str();
}

void RecipeStorageTests::serializeRecipe_ValidXmlNode_ReturnsValidRecipeId()
{
    std::string serialization = serializeSimpleRecipe();

    pugi::xml_document doc;
    doc.load_string(serialization.c_str());

    std::string id = doc.first_child().child_value("Id");

    QCOMPARE(id, "1");
}

void RecipeStorageTests::serializeRecipe_ValidXmlNode_ReturnsValidRecipeName()
{
    std::string serialization = serializeSimpleRecipe();

    pugi::xml_document doc;
    doc.load_string(serialization.c_str());

    std::string name = doc.first_child().child_value("Name");

    QVERIFY(name == "My Testing Recipe");
}

void RecipeStorageTests::serializeRecipe_ValidXmlNode_ReturnsValidRecipeDescription()
{
    std::string serialization = serializeSimpleRecipe();

    pugi::xml_document doc;
    doc.load_string(serialization.c_str());

    std::string desc = doc.first_child().child_value("Description");

    QVERIFY(desc == "This is my description");
}

void RecipeStorageTests::serializeRecipe_ValidXmlNode_ReturnsValidRecipeNumberOfPersons()
{
    std::string serialization = serializeSimpleRecipe();

    pugi::xml_document doc;
    doc.load_string(serialization.c_str());

    std::string category = doc.first_child().child_value("NumberOfPersons");

    QVERIFY(category == "1");
}

void RecipeStorageTests::serializeRecipe_ValidXmlNode_ReturnsValidRecipePrepTime()
{
    std::string serialization = serializeSimpleRecipe();

    pugi::xml_document doc;
    doc.load_string(serialization.c_str());

    std::string time = doc.first_child().child_value("PreparationTime");

    QVERIFY(time == "45");
}

void RecipeStorageTests::readRecipeSerialization_ValidXml_ReturnsValidRecipeId()
{
    Recipe recipe = m_storage.readRecipe(generateSimpleRecipeSerialization());
    QCOMPARE(recipe.getId(), 1);
}

void RecipeStorageTests::readRecipeSerialization_ValidXml_ReturnsValidRecipeName()
{
    Recipe recipe = m_storage.readRecipe(generateSimpleRecipeSerialization());
    QCOMPARE(recipe.getName(), "My Testing Recipe");
}

void RecipeStorageTests::readRecipeSerialization_ValidXml_ReturnsValidRecipeDescription()
{
    Recipe recipe = m_storage.readRecipe(generateSimpleRecipeSerialization());
    QCOMPARE(recipe.getDescription(), "This is my description");
}

void RecipeStorageTests::readRecipeSerialization_ValidXml_ReturnsValidRecipeNumberOfPersons()
{
    Recipe recipe = m_storage.readRecipe(generateSimpleRecipeSerialization());
    QCOMPARE(recipe.getNumberOfPersons(), 1);
}

void RecipeStorageTests::readRecipeSerialization_ValidXml_ReturnsValidRecipePrepTime()
{
    Recipe recipe = m_storage.readRecipe(generateSimpleRecipeSerialization());
    QCOMPARE(recipe.getPreparationTimeInMinutes(), 45);
}

void RecipeStorageTests::pugiXmlSave_WithOneRootAndTwoChildren_SaveValidXmlFile()
{
    std::string filename = "pugixml_validxml.xml";
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("RecipeStore");
    root.append_child("Test1");
    root.append_child("Test2");
    doc.save_file(filename.c_str());

    std::ifstream f(filename.c_str());
    std::string line;
    std::getline(f, line);
    std::getline(f, line);
    QVERIFY(line == "<RecipeStore>");
    std::getline(f, line);
    QVERIFY(line == "\t<Test1 />");
    std::getline(f, line);
    QVERIFY(line == "\t<Test2 />");
    std::getline(f, line);
    QVERIFY(line == "</RecipeStore>");
}

void RecipeStorageTests::pugiXmlSave_UsingAppendCopy_SaveValidXmlFile()
{
    std::string filename = "pugixml_appendcopy.xml";
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("RecipeStore");

    pugi::xml_document docFromString;
    docFromString.load_string("<Test1><SubTest1 /></Test1>");
    root.append_copy(docFromString.first_child());

    doc.save_file(filename.c_str());

    std::ifstream f(filename.c_str());
    std::string line;
    std::getline(f, line); // Skip xml declaration
    std::getline(f, line);
    QVERIFY(line == "<RecipeStore>");
    std::getline(f, line);
    QVERIFY(line == "\t<Test1>");
    std::getline(f, line);
    QVERIFY(line == "\t\t<SubTest1 />");
    std::getline(f, line);
    QVERIFY(line == "\t</Test1>");
    std::getline(f, line);
    QVERIFY(line == "</RecipeStore>");
}

void RecipeStorageTests::save_StoreWithOneRecipe_CreatesValidXmlFile()
{
    saveSimpleFileStorage();
    std::ifstream f(m_defaultFilename.c_str());
    QVERIFY(f.good());
}

void RecipeStorageTests::save_StoreWithOneRecipe_CreatesValidRootTag()
{
    saveSimpleFileStorage();
    std::ifstream f(m_defaultFilename.c_str());
    std::string line;
    std::getline(f, line); // Skip first line, xml tag definition
    std::getline(f, line);
    QVERIFY(line == "<RecipeStore>");
}

void RecipeStorageTests::save_StoreWithOneRecipe_CreatesValidContent()
{
    saveSimpleFileStorage();
    std::ifstream f(m_defaultFilename.c_str());
    std::string line;
    std::getline(f, line);
    std::getline(f, line);
    std::getline(f, line);
    std::getline(f, line);
    QCOMPARE(line, "\t<Recipe>");
    std::getline(f, line);
    QCOMPARE(line, "\t\t<Id>1</Id>");
    std::getline(f, line);
    QCOMPARE(line, "\t\t<Name>Testing recipe</Name>");
    std::getline(f, line);
    QCOMPARE(line, "\t\t<NumberOfPersons>1</NumberOfPersons>");
    std::getline(f, line);
    QCOMPARE(line, "\t\t<Description>Description of the recipe.</Description>");
    std::getline(f, line);
    QCOMPARE(line, "\t\t<PreparationTime>20</PreparationTime>");
}

#include <sstream>
#include <fstream>
#include "recipestoragetests.h"
#include "ThomChefCore/filerecipestorage.h"



RecipeStorageTests::RecipeStorageTests()
{

}

RecipeStorageTests::~RecipeStorageTests()
{

}

void RecipeStorageTests::saveSimpleFileStorage(std::string filename)
{
    FileRecipeStorage storage(filename);
    std::vector<Recipe> recipes;
    Recipe recipe("Testing recipe", Category_Standard, "Description of the recipe.", 20);
    recipe.addIngredient(Ingredient("Tomato", 1, UnitType_Number));
    recipe.addIngredient(Ingredient("Egg", 2, UnitType_Number));
    recipes.push_back(recipe);

    storage.save(recipes);
}

std::string RecipeStorageTests::serializeSimpleRecipe()
{
    FileRecipeStorage storage("test.xml");
    Recipe probingRecipe("My Testing Recipe", Category_Quick, "This is my description", 45);
    probingRecipe.addIngredient(Ingredient("Eggs", 2, UnitType_Number));
    probingRecipe.addIngredient(Ingredient("Cream", 20, UnitType_Mililiters));
    probingRecipe.addIngredient(Ingredient("Cheese", 2, UnitType_Cup));

    return storage.serializeRecipe(probingRecipe);
}

std::string RecipeStorageTests::generateSimpleRecipeSerialization()
{
    FileRecipeStorage storage("test.xml");
    pugi::xml_document doc;
    pugi::xml_node recipeNode = doc.append_child("Recipe");
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
    return ss.str();
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

void RecipeStorageTests::serializeRecipe_ValidXmlNode_ReturnsValidRecipeCategory()
{
    std::string serialization = serializeSimpleRecipe();

    pugi::xml_document doc;
    doc.load_string(serialization.c_str());

    std::string category = doc.first_child().child_value("Category");

    QVERIFY(category == "Category_Quick");
}

void RecipeStorageTests::serializeRecipe_ValidXmlNode_ReturnsValidRecipePrepTime()
{
    std::string serialization = serializeSimpleRecipe();

    pugi::xml_document doc;
    doc.load_string(serialization.c_str());

    std::string time = doc.first_child().child_value("PreparationTime");

    QVERIFY(time == "45");
}

void RecipeStorageTests::readRecipeSerialization_ValidXml_ReturnsValidRecipeName()
{
    FileRecipeStorage storage("test.xml");
    Recipe recipe = storage.readRecipe(generateSimpleRecipeSerialization());
    QVERIFY(recipe.getName() == "My Testing Recipe");
}

void RecipeStorageTests::readRecipeSerialization_ValidXml_ReturnsValidRecipeDescription()
{
    FileRecipeStorage storage("test.xml");
    Recipe recipe = storage.readRecipe(generateSimpleRecipeSerialization());
    QVERIFY(recipe.getDescription() == "This is my description");
}

void RecipeStorageTests::readRecipeSerialization_ValidXml_ReturnsValidRecipeCategory()
{
    FileRecipeStorage storage("test.xml");
    Recipe recipe = storage.readRecipe(generateSimpleRecipeSerialization());
    QVERIFY(recipe.getCategory() == Category_Quick);
}

void RecipeStorageTests::readRecipeSerialization_ValidXml_ReturnsValidRecipePrepTime()
{
    FileRecipeStorage storage("test.xml");
    Recipe recipe = storage.readRecipe(generateSimpleRecipeSerialization());
    QVERIFY(recipe.getPreparationTimeInMinutes() == 45);
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
    std::string filename = "test.xml";
    saveSimpleFileStorage(filename);
    std::ifstream f(filename.c_str());
    QVERIFY(f.good());
}

void RecipeStorageTests::save_StoreWithOneRecipe_CreatesValidRootTag()
{
    std::string filename = "test.xml";
    saveSimpleFileStorage(filename);
    std::ifstream f(filename.c_str());
    std::string line;
    std::getline(f, line); // Skip first line, xml tag definition
    std::getline(f, line);
    QVERIFY(line == "<RecipeStore>");
}

void RecipeStorageTests::save_StoreWithOneRecipe_CreatesValidContent()
{
    std::string filename = "test.xml";
    std::ifstream f(filename.c_str());
    std::string line;
    std::getline(f, line);
    std::getline(f, line);
    std::getline(f, line);
    QVERIFY(line == "\t<Recipe>");
    std::getline(f, line);
    QVERIFY(line == "\t\t<Name>Testing recipe</Name>");
    std::getline(f, line);
    QVERIFY(line == "\t\t<Category>Category_Standard</Category>");
    std::getline(f, line);
    QVERIFY(line == "\t\t<Description>Description of the recipe.</Description>");
    std::getline(f, line);
    QVERIFY(line == "\t\t<PreparationTime>20</PreparationTime>");
}

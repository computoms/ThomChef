#include "configurationstoragetests.h"
#include "configurationstorage.h"
#include "configuration.h"

ConfigurationStorageTests::ConfigurationStorageTests()
{

}

void ConfigurationStorageTests::saveToXml_WithTwoDefaultIngredients_GeneratesValidXmlForIngredientFilter()
{
    std::vector<std::string> defaultIngredients = {
        "Salt", "Pepper"
    };
    Configuration config;
    config.setDefaultIngredients(defaultIngredients);

    pugi::xml_document doc;
    ConfigurationStorage storage("test.xml");
    storage.saveToXml(config, doc);
    pugi::xml_node defIngsNode = doc.first_child().child("IngredientFilter").child("DefaultIngredients");

    QCOMPARE(doc.first_child().name(), "Configuration");
    QCOMPARE(defIngsNode.child("IngredientFilter").child_value(), "Salt");
    QCOMPARE(defIngsNode.child("IngredientFilter").next_sibling().child_value(), "Pepper");
}

void ConfigurationStorageTests::loadFromXml_WithIngredientFilterXml_GeneratesValidConfiguration()
{
    pugi::xml_document doc;
    pugi::xml_node defIngsNode = doc.append_child("Configuration").append_child("IngredientFilter").append_child("DefaultIngredients");
    defIngsNode.append_child("IngredientFilter").append_child(pugi::node_pcdata).set_value("Salt");
    defIngsNode.append_child("IngredientFilter").append_child(pugi::node_pcdata).set_value("Pepper");

    Configuration config = (ConfigurationStorage("test.xml")).readFromXml(doc);

    auto ings = config.getDefaultIngredients();
    QCOMPARE(ings.size(), 2);
    QCOMPARE(ings[0], "Salt");
    QCOMPARE(ings[1], "Pepper");
}

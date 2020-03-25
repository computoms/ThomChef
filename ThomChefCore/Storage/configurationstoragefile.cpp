#include "Storage/configurationstoragefile.h"
#include <sstream>

ConfigurationStorageFile::ConfigurationStorageFile(std::string filename):
    m_filename  (filename)
{

}

Configuration ConfigurationStorageFile::read() const
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(m_filename.c_str());
    if (!result)
        return Configuration();

    return readFromXml(doc);
}

void ConfigurationStorageFile::save(Configuration configuration) const
{
    pugi::xml_document doc;
    saveToXml(configuration, doc);

    doc.save_file(m_filename.c_str());
}

void ConfigurationStorageFile::saveToXml(Configuration configuration, pugi::xml_document &doc) const
{
    pugi::xml_node configNode = doc.append_child("Configuration");
    pugi::xml_node defaultIngredientsNode = configNode.append_child("IngredientFilter").append_child("DefaultIngredients");

    std::vector<std::string> defaultIngredients = configuration.getDefaultIngredients();
    for (const auto &ing : defaultIngredients)
        defaultIngredientsNode.append_child("IngredientFilter").append_child(pugi::node_pcdata).set_value(ing.c_str());
}

Configuration ConfigurationStorageFile::readFromXml(const pugi::xml_document &doc) const
{
    std::vector<std::string> defaultIngredients;
    pugi::xml_node configNode = doc.first_child();
    pugi::xml_node ingredientFilterNode = configNode.child("IngredientFilter");
    pugi::xml_node defaultIngCollection = ingredientFilterNode.child("DefaultIngredients");
    for (pugi::xml_node ing = defaultIngCollection.first_child(); ing; ing = ing.next_sibling("IngredientFilter"))
        defaultIngredients.push_back(ing.child_value());

    Configuration configuration;
    configuration.setDefaultIngredients(defaultIngredients);
    return configuration;
}

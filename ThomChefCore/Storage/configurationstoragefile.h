#ifndef CONFIGURATIONSTORAGE_H
#define CONFIGURATIONSTORAGE_H

#include "ThomChefCore/configuration.h"
#include "libs/pugixml-1.9/src/pugixml.hpp"

/**
 * @brief The ConfigurationStorageFile class handles storage of program configuration data
 * into a flat xml file.
 */
class ConfigurationStorageFile
{
public:
    ConfigurationStorageFile(std::string filename);

    Configuration read() const;
    void save(Configuration configuration) const;

    void saveToXml(Configuration configuration, pugi::xml_document &doc) const;
    Configuration readFromXml(const pugi::xml_document &doc) const;

private:
    std::string m_filename;
};

#endif // CONFIGURATIONSTORAGE_H

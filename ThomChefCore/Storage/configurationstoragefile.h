#ifndef CONFIGURATIONSTORAGE_H
#define CONFIGURATIONSTORAGE_H

#include "ThomChefCore/configuration.h"
#include "libs/pugixml-1.9/src/pugixml.hpp"

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

#ifndef CONFIGURATIONSTORAGETESTS_H
#define CONFIGURATIONSTORAGETESTS_H
#include <QtTest>

class ConfigurationStorageTests: public QObject
{
    Q_OBJECT

public:
    ConfigurationStorageTests();

private slots:
    void saveToXml_WithTwoDefaultIngredients_GeneratesValidXmlForIngredientFilter();
    void loadFromXml_WithIngredientFilterXml_GeneratesValidConfiguration();
};

#endif // CONFIGURATIONSTORAGETESTS_H

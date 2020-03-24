#ifndef RECIPESTORAGETESTS_H
#define RECIPESTORAGETESTS_H

#include <QtTest>
#include "ThomChefCore/filerecipestorage.h"

class RecipeStorageTests : public QObject
{
    Q_OBJECT

public:
    RecipeStorageTests();
    ~RecipeStorageTests();

private:
    void saveSimpleFileStorage();
    std::string serializeSimpleRecipe();
    std::string generateSimpleRecipeSerialization();

private slots:
    void serializeRecipe_ValidXmlNode_ReturnsValidRecipeId();
    void serializeRecipe_ValidXmlNode_ReturnsValidRecipeName();
    void serializeRecipe_ValidXmlNode_ReturnsValidRecipeDescription();
    void serializeRecipe_ValidXmlNode_ReturnsValidRecipeCategory();
    void serializeRecipe_ValidXmlNode_ReturnsValidRecipePrepTime();

    void readRecipeSerialization_ValidXml_ReturnsValidRecipeId();
    void readRecipeSerialization_ValidXml_ReturnsValidRecipeName();
    void readRecipeSerialization_ValidXml_ReturnsValidRecipeDescription();
    void readRecipeSerialization_ValidXml_ReturnsValidRecipeCategory();
    void readRecipeSerialization_ValidXml_ReturnsValidRecipePrepTime();

    void pugiXmlSave_WithOneRootAndTwoChildren_SaveValidXmlFile();
    void pugiXmlSave_UsingAppendCopy_SaveValidXmlFile();
    void save_StoreWithOneRecipe_CreatesValidXmlFile();
    void save_StoreWithOneRecipe_CreatesValidRootTag();
    void save_StoreWithOneRecipe_CreatesValidContent();

private:
    FileRecipeStorage m_storage;
    std::string m_defaultFilename;

};

#endif // RECIPESTORAGETESTS_H

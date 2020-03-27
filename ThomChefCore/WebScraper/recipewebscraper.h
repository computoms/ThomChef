#ifndef RECIPEWEBSCRAPER_H
#define RECIPEWEBSCRAPER_H
#include <QObject>
#include "../recipe.h"

class RecipeWebScraper : public QObject
{
    Q_OBJECT

public:
    virtual Recipe importRecipeFrom(std::string url) = 0;
    virtual std::vector<Recipe> importListOfRecipesFromIndexPage(std::string indexUrl) = 0;

protected:
    std::string findRaw(size_t &startingPosition, std::string opening, std::string closing) const;
    std::string findWithoutTags(size_t &startingPosition, std::string opening, std::string closing) const;
    void extractHtml(std::string url);

protected:
    std::string m_rawHtml;
};

#endif // RECIPEWEBSCRAPER_H

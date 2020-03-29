#ifndef WEBSCRAPER_H
#define WEBSCRAPER_H
#include "../recipefactory.h"
#include "recipewebscraper.h"

/**
 * @brief The RecipeImporter class manages the importation of recipes
 * from different sources.
 */
class RecipeImporter
{
public:
    RecipeImporter(RecipeFactory *factory);

    Recipe importFromWeb(std::string url) const;
    std::vector<Recipe> importListFromWeb(std::string url) const;

private:
    std::shared_ptr<RecipeWebScraper> findWebScraper(std::string url) const;

private:
    RecipeFactory *m_factory;
};

#endif // WEBSCRAPER_H

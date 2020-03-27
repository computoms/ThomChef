#ifndef WEBSCRAPER_H
#define WEBSCRAPER_H
#include "../recipe.h"
#include "recipewebscraper.h"

class RecipeImporter
{
public:
    RecipeImporter();

    Recipe importFromWeb(std::string url) const;
    std::vector<Recipe> importListFromWeb(std::string url) const;

private:
    std::shared_ptr<RecipeWebScraper> findWebScraper(std::string url) const;
};

#endif // WEBSCRAPER_H

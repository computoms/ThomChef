#ifndef WEBSCRAPER_H
#define WEBSCRAPER_H
#include "../recipe.h"
#include "recipewebscraper.h"

class RecipeImporter
{
public:
    RecipeImporter();

    Recipe importFromWeb(std::string url);

private:
    std::shared_ptr<RecipeWebScraper> findWebScraper(std::string url);
};

#endif // WEBSCRAPER_H

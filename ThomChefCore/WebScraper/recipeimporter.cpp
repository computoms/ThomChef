#include "recipeimporter.h"
#include "WebScraper/recipescrapermarmiton.h"

RecipeImporter::RecipeImporter()
{

}

Recipe RecipeImporter::importFromWeb(std::string url)
{
    std::shared_ptr<RecipeWebScraper> scraper = findWebScraper(url);
    return scraper->importRecipeFrom(url);
}

std::shared_ptr<RecipeWebScraper> RecipeImporter::findWebScraper(std::string url)
{
    // TODO parse url and find correct scraper object. For now, always Marmiton
    return std::make_shared<RecipeScraperMarmiton>();
}

#include "recipeimporter.h"
#include "WebScraper/recipescrapermarmiton.h"

RecipeImporter::RecipeImporter(RecipeFactory *factory):
    m_factory   (factory)
{

}

Recipe RecipeImporter::importFromWeb(std::string url) const
{
    std::shared_ptr<RecipeWebScraper> scraper = findWebScraper(url);
    return scraper->importRecipeFrom(url);
}

std::vector<Recipe> RecipeImporter::importListFromWeb(std::string url) const
{
    std::shared_ptr<RecipeWebScraper> scraper = findWebScraper(url);
    return scraper->importListOfRecipesFromIndexPage(url);
}

std::shared_ptr<RecipeWebScraper> RecipeImporter::findWebScraper(std::string url) const
{
    if (url.find("marmiton.org") == std::string::npos)
        throw std::invalid_argument("Only marmiton.org website is supported.");
    return std::make_shared<RecipeScraperMarmiton>(m_factory);
}

#ifndef RECIPESCRAPERMARMITON_H
#define RECIPESCRAPERMARMITON_H
#include "Import/recipewebscraper.h"
#include "recipefactory.h"

/**
 * @brief The RecipeScraperMarmiton class implements the importation of recipes
 * from the www.marmiton.org website.
 */
class RecipeScraperMarmiton : public RecipeWebScraper
{
public:
    RecipeScraperMarmiton(RecipeFactory *factory);

    virtual Recipe importRecipeFrom(std::string url) override;
    virtual std::vector<Recipe> importListOfRecipesFromIndexPage(std::string indexUrl) override;

private:
    std::vector<Ingredient> findListOfIngredients() const;
    Ingredient createIngredient(std::string ingredientName, std::string number) const;

    std::string findTitle() const;
    int findNumberOfPersons() const;
    std::string findDescription(std::string url) const;
    double findPreparationTime() const;

    bool startsWith(std::string start, std::string input) const;
    double parseTimeInMinutes(std::string timeString) const;
    std::string removeChar(std::string input, char c) const;
    std::string trim(std::string input) const;

private:
    RecipeFactory *m_factory;
};

#endif // RECIPESCRAPERMARMITON_H

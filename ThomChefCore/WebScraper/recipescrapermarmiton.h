#ifndef RECIPESCRAPERMARMITON_H
#define RECIPESCRAPERMARMITON_H
#include "WebScraper/recipewebscraper.h"

class RecipeScraperMarmiton : public RecipeWebScraper
{
public:
    RecipeScraperMarmiton();

    virtual Recipe importRecipeFrom(std::string url) override;

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
};

#endif // RECIPESCRAPERMARMITON_H

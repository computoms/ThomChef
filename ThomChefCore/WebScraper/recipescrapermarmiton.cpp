#include "recipescrapermarmiton.h"
#include "conversions.h"
#include "libs/pugixml-1.9/src/pugixml.hpp"

RecipeScraperMarmiton::RecipeScraperMarmiton(RecipeFactory *factory):
    m_factory   (factory)
{

}

Recipe RecipeScraperMarmiton::importRecipeFrom(std::string url)
{
    extractHtml(url);
    std::vector<Ingredient> ingredients = findListOfIngredients();

    std::string name = findTitle();
    std::string description = findDescription(url);
    int nbOfPersons = findNumberOfPersons();
    double timeInMinutes = findPreparationTime();

    Recipe r = m_factory->createRecipe(name, nbOfPersons, description, timeInMinutes);
    for (auto &ing : ingredients)
        r.addIngredient(ing);
    return r;
}

std::vector<Recipe> RecipeScraperMarmiton::importListOfRecipesFromIndexPage(std::string indexUrl)
{
    extractHtml(indexUrl);
    size_t start(0);
    std::string link = "";
    std::vector<std::string> urls;
    do
    {
        link = findWithoutTags(start, "<a  class=\"recipe-card-link\" href=\"", "\">");
        if (link != "")
            urls.push_back(link);
    } while (link != "");

    std::vector<Recipe> recipes;
    for (auto &url : urls)
        recipes.push_back(importRecipeFrom(url));
    return recipes;
}

std::vector<Ingredient> RecipeScraperMarmiton::findListOfIngredients() const
{
    std::vector<Ingredient> ingredients;
    size_t start(0);
    std::string ing = "";
    pugi::xml_parse_result result;
    std::string name;
    do
    {
        std::string fullBlock = findRaw(start, "<li class=\"recipe-ingredients__list__item\">", "</li>");
        pugi::xml_document doc;
        result = doc.load_string(fullBlock.c_str());
        if (!result)
            throw std::invalid_argument("Could not parse webpage. Parse result was: " + std::to_string(result.status));

        std::string number = doc.child("li").child("div").child("span").child_value();
        name = doc.child("li").child("div").child("span").next_sibling("span").child_value();
        if (name != "")
            ingredients.push_back(createIngredient(name, number));
    } while (name != "");
    return ingredients;
}

Ingredient RecipeScraperMarmiton::createIngredient(std::string ingredientName, std::string number) const
{
    if (startsWith("g ", ingredientName))
        return Ingredient(trim(ingredientName.substr(2)), Conversions::to_double(number), UnitTypes().Grammes);
    else if (startsWith("cl ", ingredientName))
        return Ingredient(trim(ingredientName.substr(3)), Conversions::to_double(number) * 10, UnitTypes().Mililiters);
    else if (startsWith("dl ", ingredientName))
        return Ingredient(trim(ingredientName.substr(3)), Conversions::to_double(number) * 100, UnitTypes().Mililiters);
    else if (startsWith("l ", ingredientName))
        return Ingredient(trim(ingredientName.substr(3)), Conversions::to_double(number), UnitTypes().Liters);
    else if (number == "")
        return Ingredient(trim(ingredientName), 1, UnitTypes().Number); // TODO "Number = Some, like some Thym or some Basilic"
    return Ingredient(trim(ingredientName), Conversions::to_double(number), UnitTypes().Number);
}

bool RecipeScraperMarmiton::startsWith(std::string start, std::string input) const
{
    return input.size() >= start.size() && input.substr(0, start.size()) == start;
}

std::string RecipeScraperMarmiton::findTitle() const
{
    size_t start(0);
    return findWithoutTags(start, "<h1 class=\"main-title \">", "</h1>");
}

int RecipeScraperMarmiton::findNumberOfPersons() const
{
    size_t start(0);
    std::string block = findRaw(start, "<div class=\"recipe-infos__quantity\">", "</div>");
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(block.c_str());
    if (!result)
        throw std::invalid_argument("Could not parse webpage. Parse result was: " + std::to_string(result.status));
    return Conversions::to_int(doc.child("div").child("span").next_sibling("span").child_value());
}

std::string RecipeScraperMarmiton::findDescription(std::string url) const
{
    size_t start(0);
    std::string block = findRaw(start, "<ol class=\"recipe-preparation__list\">", "</ol>");
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(block.c_str());
    if (!result)
        throw std::invalid_argument("Could not parse webpage. Parse result was: " + std::to_string(result.status));
    std::string description = "Imported from " + url + "\n\n";
    int index = 1;
    for (pugi::xml_node n = doc.child("ol").child("li"); n; n = n.next_sibling("li"))
    {
        description += std::to_string(index++) + ". "
                + removeChar(removeChar(n.child_value(), '\t'), '\n')
                + "\n";
    }
    return description;
}

double RecipeScraperMarmiton::findPreparationTime() const
{
    size_t start(0);
    std::string block = findRaw(start, "<div class=\"recipe-infos__total-time\">", "</div>");
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(block.c_str());
    if (!result)
        throw std::invalid_argument("Could not parse webpage. Parse result was: " + std::to_string(result.status));
    std::string time = doc.child("div").child("span").next_sibling("span").child_value();
    return parseTimeInMinutes(time);
}

double RecipeScraperMarmiton::parseTimeInMinutes(std::string timeString) const
{
    size_t hPos = timeString.find("h");
    double hours = 0;
    double minutes = 0;
    if (hPos != std::string::npos)
    {
        hours = Conversions::to_double(timeString.substr(0, hPos));
        minutes = Conversions::to_double(timeString.substr(hPos + 1, timeString.size() - hPos - 1));
    }
    else
    {
        size_t mPos = timeString.find("m");
        if (mPos != std::string::npos)
            minutes = Conversions::to_double(timeString.substr(0, mPos));
    }

    return 60 * hours + minutes;
}

std::string RecipeScraperMarmiton::removeChar(std::string input, char c) const
{
    input.erase(std::remove(input.begin(), input.end(), c), input.end());
    return input;
}

std::string RecipeScraperMarmiton::trim(std::string input) const
{
    input.erase(input.begin(),
                std::find_if(input.begin(), input.end(),
                             [](int c) { return !std::isspace(c); }));
    input.erase(std::find_if(input.rbegin(), input.rend(),
                             [](int c) { return !std::isspace(c); }).base(),
                input.end());
    return input;
}

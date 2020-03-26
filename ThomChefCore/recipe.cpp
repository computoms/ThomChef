#include "recipe.h"
#include <ctime>
#include <chrono>

Recipe::Recipe(std::string name, int numberOfPersons,
               std::string description, double preparationTimeInMinutes):
    m_name              (name),
    m_numberOfPersons   (numberOfPersons),
    m_description       (description),
    m_prepTimeInMinutes (preparationTimeInMinutes)
{
    m_id = generateGuid();
}

Recipe::Recipe(time_t id, std::string name, int numberOfPersons,
               std::string description, double prepTimeInMinutes):
    m_id                (id),
    m_name              (name),
    m_numberOfPersons   (numberOfPersons),
    m_description       (description),
    m_prepTimeInMinutes (prepTimeInMinutes)
{

}

time_t Recipe::getId() const
{
    return m_id;
}

std::string Recipe::getName() const
{
    return m_name;
}

int Recipe::getNumberOfPersons() const
{
    return m_numberOfPersons;
}

std::string Recipe::getDescription() const
{
    return m_description;
}

int Recipe::getPreparationTimeInMinutes() const
{
    return m_prepTimeInMinutes;
}

std::string Recipe::getPreparationTime() const
{
    return std::to_string(m_prepTimeInMinutes) + " min";
}

int Recipe::getNumberOfIngredients() const
{
    return m_ingredients.size();
}

Ingredient Recipe::getIngredient(int index) const
{
    if ((int)m_ingredients.size() <= index || index < 0)
        throw std::invalid_argument("The ingredient index is invalid");
    return m_ingredients[index];
}

void Recipe::addIngredient(Ingredient ingredient)
{
    m_ingredients.push_back(ingredient);
}

std::string Recipe::getFriendlyIngredients()
{
    std::string ingredientsDescription;
    for (auto &ingredient : m_ingredients)
    {
        ingredientsDescription += "- " + ingredient.getFriendlyName() + "\n";
    }

    return ingredientsDescription;
}

time_t Recipe::generateGuid()
{
    auto now = std::chrono::system_clock::now();
    time_t nowTt = std::chrono::system_clock::to_time_t(now);
    time_t reference = 1577836800; // 01-01-2020
    return nowTt - reference;
}

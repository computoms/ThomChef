#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>

#include "ingredient.h"

class Recipe
{
public:
    Recipe(std::string name, int numberOfPersons, std::string description, double preparationTimeInMinutes);
    Recipe(time_t id, std::string name, int numberOfPersons, std::string description, double prepTimeInMinutes);

    time_t getId() const;
    std::string getName() const;
    int getNumberOfPersons() const;
    std::string getDescription() const;
    int getPreparationTimeInMinutes() const;
    std::string getPreparationTime() const;
    int getNumberOfIngredients() const;
    Ingredient getIngredient(int index) const;

    void addIngredient(Ingredient ingredient);
    std::string getFriendlyIngredients();

private:
    static time_t generateGuid();

private:
    time_t m_id;
    std::string m_name;
    int m_numberOfPersons;
    std::string m_description;
    int m_prepTimeInMinutes;

    std::vector<Ingredient> m_ingredients;

};

#endif // RECIPE_H


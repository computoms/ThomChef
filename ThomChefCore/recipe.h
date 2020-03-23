#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>

#include "ingredient.h"

class Recipe
{
public:
    Recipe(std::string name, Category category, std::string description, double preparationTimeInMinutes);

    std::string getName() const;
    Category getCategory() const;
    std::string getDescription() const;
    int getPreparationTimeInMinutes() const;
    std::string getPreparationTime() const;
    int getNumberOfIngredients() const;
    Ingredient getIngredient(int index) const;

    void addIngredient(Ingredient ingredient);
    std::string getFriendlyIngredients();


private:
    std::string m_name;
    Category m_category;
    std::string m_description;
    int m_prepTimeInMinutes;

    std::vector<Ingredient> m_ingredients;

};

#endif // RECIPE_H


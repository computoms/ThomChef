#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

#include "definitions.h"

class Ingredient
{
public:
    Ingredient(std::string name, double quantity, UnitType unit);

    std::string getName() const;
    double getQuantity() const;
    UnitType getUnit() const;

    std::string getFriendlyName() const;

private:
    std::string m_name;
    double m_quantity;
    UnitType m_quantityType;

};

#endif // INGREDIENT_H

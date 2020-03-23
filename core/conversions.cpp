#include "conversions.h"
#include <sstream>
#include <exception>

Conversions::Conversions()
{

}

int Conversions::to_int(std::string input)
{
    std::stringstream ss;
    ss << input;
    int output(0);
    ss >> output;
    return output;
}

double Conversions::to_double(std::string input)
{
    std::stringstream ss;
    ss << input;
    double output(0);
    ss >> output;
    return output;
}

bool Conversions::to_bool(std::string input)
{
    std::stringstream ss;
    ss << input;
    bool output(false);
    ss >> output;
    return output;
}

UnitType Conversions::to_unitType(std::string input)
{
    if (input == "UnitType_Number")
        return UnitType_Number;
    if (input == "UnitType_Grammes")
        return UnitType_Grammes;
    if (input == "UnitType_Liters")
        return UnitType_Liters;
    if (input == "UnitType_Mililiters")
        return UnitType_Mililiters;
    if (input == "UnitType_Cup")
        return UnitType_Cup;
    if (input == "UnitType_BigSpoon")
        return UnitType_BigSpoon;
    if (input == "UnitType_TeaSpoon")
        return UnitType_TeaSpoon;
    throw std::invalid_argument("Cannot convert " + input + " to a UnitType");
}

Category Conversions::to_category(std::string input)
{
    if (input == "Category_Quick")
        return Category_Quick;
    if (input == "Category_Standard")
        return Category_Standard;
    if (input == "Category_Long")
        return Category_Long;
    throw std::invalid_argument("Cannot convert " + input + " to a Category");
}

std::string Conversions::to_string(UnitType unit)
{
    switch (unit) {
    case UnitType_Number:
        return "UnitType_Number";
    case UnitType_Grammes:
        return "UnitType_Grammes";
    case UnitType_Liters:
        return "UnitType_Liters";
    case UnitType_Mililiters:
        return "UnitType_Mililiters";
    case UnitType_Cup:
        return "UnitType_Cup";
    case UnitType_BigSpoon:
        return "UnitType_BigSpoon";
    case UnitType_TeaSpoon:
        return "UnitType_TeaSpoon";
    }
    throw std::invalid_argument("Unknown UnitType");
}

std::string Conversions::to_string(Category cat)
{
    switch (cat) {
    case Category_Quick:
        return "Category_Quick";
    case Category_Standard:
        return "Category_Standard";
    case Category_Long:
        return "Category_Long";
    }
    throw std::invalid_argument("Unknown Category");
}

std::string Conversions::to_string(double quantity)
{
    std::string result = std::to_string(quantity);
    // Remove trailing zeros
    result.erase(result.find_last_not_of('0') + 1, std::string::npos);
    if (result[result.length() - 1] == '.')
        result = result.substr(0, result.length() - 1);
    return result;
}

std::string Conversions::to_friendlyUnit(UnitType unit)
{
    switch (unit) {
    case UnitType_Number:
        return "";
    case UnitType_Grammes:
        return "g";
    case UnitType_Liters:
        return "L";
    case UnitType_Mililiters:
        return "mL";
    case UnitType_Cup:
        return "cup";
    case UnitType_BigSpoon:
        return "b.s.";
    case UnitType_TeaSpoon:
        return "t.s.";
    }
    throw std::invalid_argument("Unknown UnitType");
}

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

time_t Conversions::to_time_t(std::string input)
{
    std::stringstream ss;
    ss << input;
    time_t output(0);
    ss >> output;
    return output;
}

UnitType Conversions::to_unitType(std::string input, bool isFriendlyName)
{
    for (auto &type : (UnitTypes()).getTypes())
    {
        if (isFriendlyName && input == type.friendlyName)
            return type;
        if (!isFriendlyName && input == type.serialization)
            return type;
    }
    throw std::invalid_argument("Cannot convert " + input + " to a UnitType");
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

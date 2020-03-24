#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include <string>

#include "definitions.h"

class Conversions
{
public:
    Conversions();

    static int to_int(std::string input);
    static double to_double(std::string input);
    static bool to_bool(std::string input);
    static time_t to_time_t(std::string input);

    static UnitType to_unitType(std::string input, bool isFriendlyName);
    static Category to_category(std::string input, bool isFriendlyName);

    static std::string to_string(double quantity);

    static std::string to_friendlyUnit(UnitType unit);
};

#endif // CONVERSIONS_H

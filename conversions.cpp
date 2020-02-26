#include "conversions.h"
#include <sstream>

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

bool Conversions::to_bool(std::string input)
{
    std::stringstream ss;
    ss << input;
    bool output(false);
    ss >> output;
    return output;
}

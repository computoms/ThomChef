#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include <string>

class Conversions
{
public:
    Conversions();

    static int to_int(std::string input);
    static bool to_bool(std::string input);
};

#endif // CONVERSIONS_H

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>
#include <vector>

struct EnumValue
{
    EnumValue(int c, std::string s, std::string fName)
    {
        code = c;
        serialization = s;
        friendlyName = fName;
    }

    bool operator==(const EnumValue &other)
    {
        return other.code == code;
    }

    int code;
    std::string serialization;
    std::string friendlyName;
};

struct UnitType : public EnumValue
{
    UnitType(int c, std::string s, std::string fName): EnumValue(c, s, fName) {}
};

class UnitTypes
{
public:
    const UnitType Number      = UnitType(0, "UnitType_Number", "Number");
    const UnitType Grammes     = UnitType(1, "UnitType_Grammes", "g");
    const UnitType Liters      = UnitType(2, "UnitType_Liters", "L");
    const UnitType Mililiters  = UnitType(3, "UnitType_Mililiters", "mL");
    const UnitType Cup         = UnitType(4, "UnitType_Cup", "cup");
    const UnitType TeaSpoon    = UnitType(5, "UnitType_TeaSpoon", "tea spoon");
    const UnitType BigSpon     = UnitType(6, "UnitType_BigSpoon", "big spoon");

    static std::vector<UnitType> getTypes()
    {
        UnitTypes types;
        std::vector<UnitType> allTypes = {
            types.Number, types.Grammes, types.Liters, types.Mililiters, types.Cup, types.TeaSpoon, types.BigSpon
        };
        return allTypes;
    }
};

#endif // DEFINITIONS_H

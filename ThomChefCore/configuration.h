#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <memory>
#include <vector>
#include <string>

/**
 * @brief The Configuration class holds the program configuration options
 * that can be modified by the user.
 */
class Configuration
{
public:
    Configuration();

    std::vector<std::string> getDefaultIngredients() const;
    void setDefaultIngredients(std::vector<std::string> defaultIngredients);
    std::string getEmailAddress() const;
    void setEmailAddress(std::string emailAddress);

private:
    std::vector<std::string> m_defaultIngredients;
    std::string m_emailAddress;
};

#endif // CONFIGURATION_H

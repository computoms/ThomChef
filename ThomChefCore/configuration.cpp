#include "configuration.h"

Configuration::Configuration()
{

}

std::vector<std::string> Configuration::getDefaultIngredients() const
{
    return m_defaultIngredients;
}

void Configuration::setDefaultIngredients(std::vector<std::string> defaultIngredients)
{
    m_defaultIngredients = defaultIngredients;
}

std::string Configuration::getEmailAddress() const
{
    return m_emailAddress;
}

void Configuration::setEmailAddress(std::string emailAddress)
{
    m_emailAddress = emailAddress;
}

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

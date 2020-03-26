#include "recipenamefilter.h"

RecipeNameFilter::RecipeNameFilter()
{

}

bool RecipeNameFilter::isInFilter(const Recipe &recipe) const
{
    // Transform to lower-case string
    std::string recipeName = recipe.getName();
    std::transform(recipeName.begin(), recipeName.end(), recipeName.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    std::string filter = m_recipeName;
    std::transform(filter.begin(), filter.end(), filter.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return recipeName.find(filter) != std::string::npos;
}

void RecipeNameFilter::setRecipeName(std::string recipeName)
{
    m_recipeName = recipeName;
    filterUpdated();
}

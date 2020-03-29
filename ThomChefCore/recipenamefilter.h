#ifndef RECIPENAMEFILTER_H
#define RECIPENAMEFILTER_H
#include "filter.h"

/**
 * @brief The RecipeNameFilter class filters the Recipe(s) by name, when
 * added to the RecipeStore filters.
 */
class RecipeNameFilter : public Filter
{
public:
    RecipeNameFilter();

    virtual bool isInFilter(const Recipe &recipe) const override;
    void setRecipeName(std::string recipeName);

private:
    std::string m_recipeName;
};

#endif // RECIPENAMEFILTER_H

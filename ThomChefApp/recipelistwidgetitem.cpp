#include "recipelistwidgetitem.h"


RecipeListWidgetItem::RecipeListWidgetItem(time_t id, QString title):
    QListWidgetItem (title),
    m_id            (id)
{

}

time_t RecipeListWidgetItem::getId() const
{
    return m_id;
}

#include "recipelistwidgetitem.h"


RecipeListWidgetItem::RecipeListWidgetItem(QListWidget *parent, time_t id, QString title):
    QListWidgetItem (title, parent),
    m_id            (id)
{

}

time_t RecipeListWidgetItem::getId() const
{
    return m_id;
}

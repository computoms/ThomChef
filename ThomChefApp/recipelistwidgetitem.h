#ifndef RECIPELISTWIDGETITEM_H
#define RECIPELISTWIDGETITEM_H

#include <QListWidgetItem>

/**
 * @brief Subclass of QListWidgetItem that holds the recipe Id in addition to
 * its name so that we can find the recipe in the data store using its Id.
 */
class RecipeListWidgetItem : public QListWidgetItem
{
public:
    RecipeListWidgetItem(QListWidget *parent, time_t id, QString title);

    time_t getId() const;

private:
    time_t m_id;
};

#endif // RECIPELISTWIDGETITEM_H

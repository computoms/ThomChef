#ifndef RECIPELISTWIDGETITEM_H
#define RECIPELISTWIDGETITEM_H

#include <QListWidgetItem>


class RecipeListWidgetItem : public QListWidgetItem
{
public:
    RecipeListWidgetItem(QListWidget *parent, time_t id, QString title);

    time_t getId() const;

private:
    time_t m_id;
};

#endif // RECIPELISTWIDGETITEM_H

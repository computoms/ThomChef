#ifndef SHOPPINGLISTVIEW_H
#define SHOPPINGLISTVIEW_H

#include <QDialog>
#include "ThomChefCore/ingredient.h"

namespace Ui {
class ShoppingListView;
}

class ShoppingListView : public QDialog
{
    Q_OBJECT

public:
    explicit ShoppingListView(QWidget *parent = nullptr);
    ~ShoppingListView();

    void setIngredients(std::vector<Ingredient> ingredients);

private:
    Ui::ShoppingListView *ui;
    std::vector<Ingredient> m_ingredients;
};

#endif // SHOPPINGLISTVIEW_H

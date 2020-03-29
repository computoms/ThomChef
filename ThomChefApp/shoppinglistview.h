#ifndef SHOPPINGLISTVIEW_H
#define SHOPPINGLISTVIEW_H

#include <QDialog>
#include "ThomChefCore/ingredient.h"

namespace Ui {
class ShoppingListView;
}

/**
 * @brief Implementation of the view that displays the shopping list.
 */
class ShoppingListView : public QDialog
{
    Q_OBJECT

public:
    explicit ShoppingListView(QWidget *parent = nullptr);
    ~ShoppingListView();

    void setIngredients(std::vector<Ingredient> ingredients);
    void setDefaultEmailAddress(std::string emailAddress);
    std::string getEmailAddress() const;

private slots:
    void on_button_sendEmail_clicked();

private:
    void sendByEmail(std::string emailAddress);
    void sendToReminders();

private:
    Ui::ShoppingListView *ui;
    std::vector<Ingredient> m_ingredients;
};

#endif // SHOPPINGLISTVIEW_H

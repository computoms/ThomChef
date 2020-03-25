#ifndef ADDRECIPE_H
#define ADDRECIPE_H

#include <QDialog>
#include "ThomChefCore/recipestore.h"

namespace Ui {
class AddRecipe;
}

class AddRecipe : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecipe(QWidget *parent = nullptr, RecipeStore *recipeStore = nullptr);
    AddRecipe(QWidget *parent, RecipeStore *recipeStore, Recipe selectedRecipe);
    ~AddRecipe();

    void init();
    void clearAll();

private slots:
    void on_buttonBox_accepted();

    void on_ingredient_buttonadd_clicked();

    void on_button_ingredient_delete_clicked();

private:
    void addCurrentRecipe();
    void addCurrentIngredientAndClearIngredient();
    void deleteIngredient(std::string ingredientDescription);

private:
    Ui::AddRecipe *ui;
    RecipeStore *m_store;
    Recipe m_selectedRecipe;
    bool m_isModifyingRecipe;
    std::vector<Ingredient> m_currentIngredients;
};

#endif // ADDRECIPE_H

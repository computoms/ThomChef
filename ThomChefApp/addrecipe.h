#ifndef ADDRECIPE_H
#define ADDRECIPE_H

#include <QDialog>
#include "ThomChefCore/recipe.h"
#include "ThomChefCore/recipefactory.h"

namespace Ui {
class AddRecipe;
}

class AddRecipe : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecipe(QWidget *parent = nullptr, RecipeFactory *factory = nullptr);
    AddRecipe(QWidget *parent, RecipeFactory *factory, Recipe selectedRecipe);
    ~AddRecipe();

    void init();
    Recipe getNewRecipe();

private slots:

    void on_ingredient_buttonadd_clicked();

    void on_button_ingredient_delete_clicked();

private:
    void addCurrentIngredientAndClearIngredient();
    void deleteIngredient(std::string ingredientDescription);

private:
    Ui::AddRecipe *ui;
    RecipeFactory *m_factory;
    Recipe m_selectedRecipe;
    bool m_isModifyingRecipe;
    std::vector<Ingredient> m_currentIngredients;
};

#endif // ADDRECIPE_H

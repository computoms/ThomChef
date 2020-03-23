#ifndef ADDRECIPE_H
#define ADDRECIPE_H

#include <QDialog>
#include "core/recipestore.h"

namespace Ui {
class AddRecipe;
}

class AddRecipe : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecipe(QWidget *parent = nullptr, std::shared_ptr<RecipeStore> recipeStore = nullptr);
    ~AddRecipe();

    void init();
    void clearAll();

private slots:
    void on_buttonBox_accepted();

    void on_ingredient_buttonadd_clicked();

private:
    void addCurrentRecipeAndClear();
    void addCurrentIngredientAndClearIngredient();

private:
    Ui::AddRecipe *ui;
    std::shared_ptr<RecipeStore> m_store;
    std::vector<Ingredient> m_currentIngredients;
};

#endif // ADDRECIPE_H

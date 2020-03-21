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
    explicit AddRecipe(QWidget *parent = nullptr);
    ~AddRecipe();

    void clearAll();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddRecipe *ui;
    std::shared_ptr<RecipeStore> m_store;
};

#endif // ADDRECIPE_H

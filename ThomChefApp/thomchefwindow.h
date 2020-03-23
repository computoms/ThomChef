#ifndef THOMCHEFWINDOW_H
#define THOMCHEFWINDOW_H

#include <QMainWindow>

#include "ThomChefCore/recipestore.h"

namespace Ui {
class ThomChefWindow;
}

class ThomChefWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ThomChefWindow(QWidget *parent = nullptr);
    ~ThomChefWindow();

    void initialize();

private slots:
    void on_button_addrecipe_clicked();

    void on_listrecipes_itemSelectionChanged();

    void on_button_deleteRecipe_clicked();

    void on_button_updateRecipe_clicked();

    void on_store_changed();

private:
    void updateRecipeList();
    void updateSelectedRecipe();
    void modifySelectedRecipe();
    void deleteSelectedRecipe();

private:
    Ui::ThomChefWindow *ui;
    std::shared_ptr<FileRecipeStorage> m_storage;
    std::shared_ptr<RecipeStore> m_store;
    bool m_updating;
};

#endif // THOMCHEFWINDOW_H

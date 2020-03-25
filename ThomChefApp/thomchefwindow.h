#ifndef THOMCHEFWINDOW_H
#define THOMCHEFWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "ThomChefCore/recipestore.h"
#include "ThomChefCore/configuration.h"

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

    void on_button_findRecipe_add_clicked();

    void on_button_ingredientfilter_remove_clicked();

private:
    void updateRecipeList();
    void updateSelectedRecipe();
    void modifySelectedRecipe();
    void deleteSelectedRecipe();
    time_t getCurrentRecipeId() const;
    void addIngredientFilter(std::string filter);
    void removeIngredientFilter(std::string filter);

private:
    Ui::ThomChefWindow *ui;
    std::shared_ptr<FileRecipeStorage> m_storage;
    std::shared_ptr<RecipeStore> m_store;
    std::shared_ptr<IngredientFilter> m_filter;
    Configuration m_configuration;
    bool m_updating;
};

#endif // THOMCHEFWINDOW_H

#ifndef THOMCHEFWINDOW_H
#define THOMCHEFWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "ThomChefCore/recipestore.h"
#include "ThomChefCore/Storage/configurationstoragefile.h"
#include "ThomChefCore/Storage/recipestoragefile.h"
#include "ThomChefCore/configuration.h"
#include "ThomChefCore/randomrecipeselector.h"

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

    void on_button_filter_configure_clicked();

    void on_edit_ingredientFilter_returnPressed();

    void on_edit_ingredientFilter_textChanged(const QString &arg1);

    void on_button_ingredientfilter_clear_clicked();

    void on_button_generateRecipes_clicked();

    void on_button_showShoppingList_clicked();

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
    ConfigurationStorageFile m_configurationStorage;
    RecipeStorageFile m_storage;
    Configuration m_configuration;
    RecipeStore m_store;
    IngredientFilter m_filter;
    RandomRecipeSelector m_recipeSelector;
    bool m_updating;
};

#endif // THOMCHEFWINDOW_H


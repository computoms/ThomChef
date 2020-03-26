#include "thomchefwindow.h"
#include "ui_thomchefwindow.h"
#include "addrecipe.h"
#include "viewutils.h"
#include "recipelistwidgetitem.h"
#include "filtersettingsview.h"
#include "shoppinglistview.h"

#include "ThomChefCore/Storage/recipestoragefile.h"
#include "ThomChefCore/Storage/configurationstoragefile.h"
#include <ios>

ThomChefWindow::ThomChefWindow(QWidget *parent) :
    QMainWindow             (parent),
    ui                      (new Ui::ThomChefWindow),
    m_configurationStorage  ("configuration.xml"),
    m_storage               ("recipes.xml"),
    m_store                 (&m_storage),
    m_recipeSelector        (&m_store),
    m_updating              (false)
{
    ui->setupUi(this);

    connect(&m_store, SIGNAL(changed()), this, SLOT(on_store_changed()));
}

ThomChefWindow::~ThomChefWindow()
{
    delete ui;
}

void ThomChefWindow::initialize()
{
    try
    {
        m_store.initialize();
        updateRecipeList();
        ConfigurationStorageFile configStorage("configuration.xml");
        m_configuration = configStorage.read();
        m_filter.setDefaultIngredients(m_configuration.getDefaultIngredients());

        ui->button_ingredientfilter_remove->setEnabled(false);
        ui->button_findRecipe_add->setEnabled(false);
        ui->button_showShoppingList->setEnabled(false);
        ui->button_ingredientfilter_clear->setEnabled(false);
        ui->edit_generate_numberOfMeals->setValue(1);
        ui->edit_generate_numberOfMeals->setRange(1, m_store.getNumberOfRecipes());
    }
    catch (std::ios_base::failure f)
    {
        ViewUtils::showError(f.what());
        m_updating = false;
    }
}

void ThomChefWindow::on_button_addrecipe_clicked()
{
    AddRecipe addRecipeView(this);
    int result = addRecipeView.exec();

    if (result == QDialog::Accepted)
        m_store.addRecipe(addRecipeView.getNewRecipe());
}

void ThomChefWindow::on_listrecipes_itemSelectionChanged()
{
    try
    {
        updateSelectedRecipe();
    }
    catch (std::invalid_argument e)
    {
        ViewUtils::showError(e.what());
    }
}

void ThomChefWindow::on_button_deleteRecipe_clicked()
{
    try
    {
        if (ui->listrecipes->currentItem() == nullptr)
            return;

        deleteSelectedRecipe();
    }
    catch (std::invalid_argument e)
    {
        ViewUtils::showError(e.what());
    }
}

void ThomChefWindow::on_button_updateRecipe_clicked()
{
    try
    {
        if (ui->listrecipes->currentItem() == nullptr)
            return;

        modifySelectedRecipe();
    }
    catch (std::invalid_argument e)
    {
        ViewUtils::showError(e.what());
    }
}

void ThomChefWindow::on_store_changed()
{
    try
    {
        updateRecipeList();
    }
    catch (std::invalid_argument e)
    {
        ViewUtils::showError(e.what());
        m_updating = false;
    }
}

void ThomChefWindow::on_button_findRecipe_add_clicked()
{
    try {
        addIngredientFilter(ui->edit_ingredientFilter->text().toStdString());
        ui->listIngredientFilters->addItem(ui->edit_ingredientFilter->text());
        ui->edit_ingredientFilter->setText("");
        if (!ui->button_ingredientfilter_remove->isEnabled())
            ui->button_ingredientfilter_remove->setEnabled(true);
        if (!ui->button_ingredientfilter_clear->isEnabled())
            ui->button_ingredientfilter_clear->setEnabled(true);
    }
    catch (std::invalid_argument e)
    {
        ViewUtils::showError(e.what());
    }
}

void ThomChefWindow::on_button_ingredientfilter_remove_clicked()
{
    try
    {
        if (ui->listIngredientFilters->currentItem() == nullptr)
            return;

        removeIngredientFilter(ui->listIngredientFilters->currentItem()->text().toStdString());
        ui->listIngredientFilters->takeItem(ui->listIngredientFilters->currentRow());

        if (m_filter.isEmpty())
        {
            ui->button_ingredientfilter_remove->setEnabled(false);
            ui->button_ingredientfilter_clear->setEnabled(false);
        }
        else
        {
            if (!ui->button_ingredientfilter_remove->isEnabled())
                ui->button_ingredientfilter_remove->setEnabled(true);
            if (!ui->button_ingredientfilter_clear->isEnabled())
                ui->button_ingredientfilter_clear->setEnabled(false);
        }
    }
    catch (std::invalid_argument e)
    {
        ViewUtils::showError(e.what());
    }
}

void ThomChefWindow::on_button_filter_configure_clicked()
{
    FilterSettingsView settings(this);
    settings.init(m_configuration);
    settings.exec();
    m_configuration.setDefaultIngredients(settings.getDefaultIngredients());
    m_configurationStorage.save(m_configuration);
}

void ThomChefWindow::on_edit_ingredientFilter_returnPressed()
{
    on_button_findRecipe_add_clicked();
}

void ThomChefWindow::on_edit_ingredientFilter_textChanged(const QString &arg1)
{
    if (!ui->button_findRecipe_add->isEnabled() && arg1 != "")
        ui->button_findRecipe_add->setEnabled(true);
    else if (ui->button_findRecipe_add->isEnabled() && arg1 == "")
        ui->button_findRecipe_add->setEnabled(false);
}

void ThomChefWindow::on_button_ingredientfilter_clear_clicked()
{
    try
    {
        for (auto &item : ui->listIngredientFilters->findItems("*", Qt::MatchWildcard))
        {
            removeIngredientFilter(item->text().toStdString());
        }
        ui->listIngredientFilters->clear();
        ui->button_ingredientfilter_remove->setEnabled(false);
    }
    catch (std::invalid_argument e)
    {
        ViewUtils::showError(e.what());
    }
}

void ThomChefWindow::on_button_generateRecipes_clicked()
{
    try
    {
        ui->listGenerateRecipes->clear();
        int nbOfMeals = ui->edit_generate_numberOfMeals->value();
        for (auto &recipe : m_recipeSelector.selectRecipes(nbOfMeals))
            ui->listGenerateRecipes->addItem(recipe.getName().c_str());

        if (!ui->button_showShoppingList->isEnabled())
            ui->button_showShoppingList->setEnabled(true);
    }
    catch (std::invalid_argument e)
    {
        ViewUtils::showError(e.what());
    }
}

void ThomChefWindow::on_button_showShoppingList_clicked()
{
    ShoppingListView view(this);
    view.setIngredients(m_recipeSelector.getListOfIngredients());
    view.setDefaultEmailAddress(m_configuration.getEmailAddress());
    view.exec();
    m_configuration.setEmailAddress(view.getEmailAddress());
    m_configurationStorage.save(m_configuration);
}

void ThomChefWindow::updateRecipeList()
{
    m_updating = true;
    ui->listrecipes->clear();
    int nbRecipes = m_store.getNumberOfRecipes();
    for (int i = 0; i < nbRecipes; ++i)
    {
        Recipe recipe = m_store.getRecipe(i);
        ui->listrecipes->addItem(new RecipeListWidgetItem(recipe.getId(), recipe.getName().c_str()));
    }
    m_updating = false;
    if (nbRecipes > 0)
    {
        ui->listrecipes->setCurrentRow(0);
        if (!ui->button_updateRecipe->isEnabled())
            ui->button_updateRecipe->setEnabled(true);
        if (!ui->button_deleteRecipe->isEnabled())
            ui->button_deleteRecipe->setEnabled(true);
    }
    else
    {
        ui->button_updateRecipe->setEnabled(false);
        ui->button_deleteRecipe->setEnabled(false);
    }
}

void ThomChefWindow::updateSelectedRecipe()
{
    if (m_updating)
        return;

    Recipe recipe = m_store.findRecipe(getCurrentRecipeId());
    ui->label_recipeName->setText(recipe.getName().c_str());
    ui->label_numberOfPersons->setText(std::to_string(recipe.getNumberOfPersons()).c_str());
    ui->label_recipeIngredients->setText(recipe.getFriendlyIngredients().c_str());
    ui->label_recipeTime->setText(recipe.getPreparationTime().c_str());
    ui->label_recipeDescription->setText(recipe.getDescription().c_str());
}

void ThomChefWindow::modifySelectedRecipe()
{
    Recipe recipe = m_store.findRecipe(getCurrentRecipeId());

    AddRecipe addRecipeView(this, recipe);
    int result = addRecipeView.exec();

    if (result == QDialog::Accepted)
        m_store.updateRecipe(addRecipeView.getNewRecipe());
}

void ThomChefWindow::deleteSelectedRecipe()
{
    Recipe recipe = m_store.findRecipe(getCurrentRecipeId());
    m_store.deleteRecipe(recipe);
}

time_t ThomChefWindow::getCurrentRecipeId() const
{
    RecipeListWidgetItem *currentItem = dynamic_cast<RecipeListWidgetItem*>(ui->listrecipes->currentItem());
    return currentItem->getId();
}

void ThomChefWindow::addIngredientFilter(std::string filter)
{
    m_filter.addIngredientFilter(filter);
    if (!m_store.hasFilter())
        m_store.setFilter(&m_filter);
}

void ThomChefWindow::removeIngredientFilter(std::string filter)
{
    m_filter.removeIngredientFilter(filter);
    if (m_filter.isEmpty() && m_store.hasFilter())
        m_store.removeFilter();
}

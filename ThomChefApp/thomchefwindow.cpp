#include "thomchefwindow.h"
#include "ui_thomchefwindow.h"
#include "addrecipe.h"
#include "viewutils.h"
#include "recipelistwidgetitem.h"
#include "filtersettingsview.h"

#include "ThomChefCore/Storage/recipestoragefile.h"
#include "ThomChefCore/Storage/configurationstoragefile.h"
#include <ios>

ThomChefWindow::ThomChefWindow(QWidget *parent) :
    QMainWindow             (parent),
    ui                      (new Ui::ThomChefWindow),
    m_configurationStorage  ("configuration.xml"),
    m_storage               ("recipes.xml"),
    m_store                 (&m_storage),
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
    }
    catch (std::ios_base::failure f)
    {
        ViewUtils::showError(f.what());
        m_updating = false;
    }
}

void ThomChefWindow::on_button_addrecipe_clicked()
{
    AddRecipe addRecipeView(this, &m_store);
    addRecipeView.setAttribute(Qt::WA_DeleteOnClose, true);
    addRecipeView.exec();
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
    ui->label_recipeIngredients->setText(recipe.getFriendlyIngredients().c_str());
    ui->label_recipeTime->setText(recipe.getPreparationTime().c_str());
    ui->label_recipeDescription->setText(recipe.getDescription().c_str());
}

void ThomChefWindow::modifySelectedRecipe()
{
    Recipe recipe = m_store.findRecipe(getCurrentRecipeId());

    AddRecipe addRecipeView(this, &m_store, recipe);
    addRecipeView.setAttribute(Qt::WA_DeleteOnClose, true);
    addRecipeView.exec();
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
        removeIngredientFilter(ui->listIngredientFilters->currentItem()->text().toStdString());
        ui->listIngredientFilters->takeItem(ui->listIngredientFilters->currentRow());
        if (m_filter.isEmpty())
            ui->button_ingredientfilter_remove->setEnabled(false);
        else if (!ui->button_ingredientfilter_remove->isEnabled())
            ui->button_ingredientfilter_remove->setEnabled(true);
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

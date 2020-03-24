#include "thomchefwindow.h"
#include "ui_thomchefwindow.h"
#include "addrecipe.h"
#include "viewutils.h"
#include "recipelistwidgetitem.h"

#include "ThomChefCore/filerecipestorage.h"
#include <ios>

ThomChefWindow::ThomChefWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThomChefWindow),
    m_updating  (false)
{
    ui->setupUi(this);
    m_storage = std::make_shared<FileRecipeStorage>("recipes.xml");
    m_store = std::make_shared<RecipeStore>(m_storage);
    connect(m_store.get(), SIGNAL(changed()), this, SLOT(on_store_changed()));
}

ThomChefWindow::~ThomChefWindow()
{
    delete ui;
}

void ThomChefWindow::initialize()
{
    try
    {
        m_store->initialize();
        updateRecipeList();
    }
    catch (std::ios_base::failure f)
    {
        ViewUtils::showError(f.what());
        m_updating = false;
    }
}

void ThomChefWindow::on_button_addrecipe_clicked()
{
    AddRecipe *addRecipeView = new AddRecipe(this, m_store);
    addRecipeView->setAttribute(Qt::WA_DeleteOnClose, true);
    addRecipeView->exec();
}

void ThomChefWindow::updateRecipeList()
{
    m_updating = true;
    ui->listrecipes->clear();
    int nbRecipes = m_store->getNumberOfRecipes();
    for (int i = 0; i < nbRecipes; ++i)
    {
        Recipe recipe = m_store->getRecipe(i);
        ui->listrecipes->addItem(recipe.getName().c_str());
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

    Recipe recipe = m_store->findRecipe(getCurrentRecipeId());
    ui->label_recipeName->setText(recipe.getName().c_str());
    ui->label_recipeIngredients->setText(recipe.getFriendlyIngredients().c_str());
    ui->label_recipeTime->setText(recipe.getPreparationTime().c_str());
    ui->label_recipeDescription->setText(recipe.getDescription().c_str());
}

void ThomChefWindow::modifySelectedRecipe()
{
    Recipe recipe = m_store->findRecipe(getCurrentRecipeId());

    AddRecipe *addRecipeView = new AddRecipe(this, m_store, recipe);
    addRecipeView->setAttribute(Qt::WA_DeleteOnClose, true);
    addRecipeView->show();
}

void ThomChefWindow::deleteSelectedRecipe()
{
    Recipe recipe = m_store->findRecipe(getCurrentRecipeId());
    m_store->deleteRecipe(recipe);
}

time_t ThomChefWindow::getCurrentRecipeId() const
{
    RecipeListWidgetItem *currentItem = dynamic_cast<RecipeListWidgetItem*>(ui->listrecipes->currentItem());
    return currentItem->getId();
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


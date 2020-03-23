#include "thomchefwindow.h"
#include "ui_thomchefwindow.h"
#include "addrecipe.h"
#include "viewutils.h"

#include "core/filerecipestorage.h"
#include "core/conversions.h"
#include <ios>

ThomChefWindow::ThomChefWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThomChefWindow)
{
    ui->setupUi(this);
    m_storage = std::make_shared<FileRecipeStorage>("recipes.xml");
    m_store = std::make_shared<RecipeStore>(m_storage);
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
    }
}

void ThomChefWindow::on_button_addrecipe_clicked()
{
    AddRecipe *addRecipeView = new AddRecipe(this, m_store);
    addRecipeView->show();
}

void ThomChefWindow::updateRecipeList()
{
    ui->listrecipes->clear();
    int nbRecipes = m_store->getNumberOfRecipes();
    for (int i = 0; i < nbRecipes; ++i)
    {
        Recipe recipe = m_store->getRecipe(i);
        ui->listrecipes->addItem(recipe.getName().c_str());
    }
}

void ThomChefWindow::updateSelectedRecipe()
{
    Recipe recipe = m_store->findRecipeByName(ui->listrecipes->currentItem()->text().toStdString());
    ui->label_recipeName->setText(recipe.getName().c_str());
    ui->label_recipeIngredients->setText(recipe.getFriendlyIngredients().c_str());
    ui->label_recipeTime->setText(recipe.getPreparationTime().c_str());
    ui->label_recipeDescription->setText(recipe.getDescription().c_str());
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

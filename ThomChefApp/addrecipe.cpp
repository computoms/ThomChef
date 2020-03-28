#include "addrecipe.h"
#include "ui_addrecipe.h"

#include "ThomChefCore/conversions.h"
#include "ThomChefCore/recipe.h"
#include "viewutils.h"

AddRecipe::AddRecipe(QWidget *parent, RecipeFactory *factory) :
    QDialog             (parent),
    ui                  (new Ui::AddRecipe),
    m_factory           (factory),
    m_selectedRecipe    (0, "", 1, "", 0),
    m_isModifyingRecipe (false)
{
    ui->setupUi(this);
    init();
}

AddRecipe::AddRecipe(QWidget *parent, RecipeFactory *factory, Recipe selectedRecipe):
    QDialog             (parent),
    ui                  (new Ui::AddRecipe),
    m_factory           (factory),
    m_selectedRecipe    (selectedRecipe),
    m_isModifyingRecipe (true)
{
    ui->setupUi(this);
    init();
}

AddRecipe::~AddRecipe()
{
    delete ui;
}

void AddRecipe::init()
{
    for (auto &type : UnitTypes::getTypes())
        ui->ingredient_choose_unit->addItem(type.friendlyName.c_str());

    if (m_isModifyingRecipe)
    {
        ui->edit_name->setText(m_selectedRecipe.getName().c_str());
        ui->edit_time->setText(std::to_string(m_selectedRecipe.getPreparationTimeInMinutes()).c_str());
        ui->edit_description->setPlainText(m_selectedRecipe.getDescription().c_str());

        int nbIngredients = m_selectedRecipe.getNumberOfIngredients();
        for (int i = 0; i < nbIngredients; ++i)
        {
            ui->ingredientlist->addItem(m_selectedRecipe.getIngredient(i).getFriendlyName().c_str());
            m_currentIngredients.push_back(m_selectedRecipe.getIngredient(i));
        }
    }
}

Recipe AddRecipe::getNewRecipe()
{
    std::string name = ui->edit_name->text().toStdString();
    int numberOfPersons = ui->edit_numberOfPersons->value();
    std::string description = ui->edit_description->toPlainText().toStdString();
    double time = Conversions::to_double(ui->edit_time->text().toStdString());

    Recipe recipe = m_factory->createRecipe(name, numberOfPersons, description, time);
    for (auto &ing : m_currentIngredients)
        recipe.addIngredient(ing);
    return recipe;
}

void AddRecipe::addCurrentIngredientAndClearIngredient()
{
    std::string name = ui->ingredient_edit_name->text().toStdString();
    double quantity = Conversions::to_double(ui->ingredient_edit_quantity->text().toStdString());
    UnitType unit = Conversions::to_unitType(ui->ingredient_choose_unit->currentText().toStdString(), true);
    Ingredient ingredient(name, quantity, unit);

    ui->ingredientlist->addItem(ingredient.getFriendlyName().c_str());
    m_currentIngredients.push_back(ingredient);

    ui->ingredient_edit_name->setText("");
    ui->ingredient_edit_quantity->setText("");
    ui->ingredient_choose_unit->setCurrentIndex(0);
}

void AddRecipe::deleteIngredient(std::string ingredientDescription)
{
    for (auto it = m_currentIngredients.begin(); it != m_currentIngredients.end(); ++it)
    {
        if (it->getFriendlyName() == ingredientDescription)
        {
            m_currentIngredients.erase(it);
            break;
        }
    }
}

void AddRecipe::on_ingredient_buttonadd_clicked()
{
    try
    {
        addCurrentIngredientAndClearIngredient();
    }
    catch (std::invalid_argument e)
    {
        ViewUtils::showError(e.what());
    }
}


void AddRecipe::on_button_ingredient_delete_clicked()
{
    try
    {
        deleteIngredient(ui->ingredientlist->currentItem()->text().toStdString());
        ui->ingredientlist->takeItem(ui->ingredientlist->currentRow());
    }
    catch (std::invalid_argument e)
    {
        ViewUtils::showError(e.what());
    }
}

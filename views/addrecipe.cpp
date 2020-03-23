#include "addrecipe.h"
#include "ui_addrecipe.h"

#include "core/conversions.h"
#include "core/recipe.h"
#include "viewutils.h"
#include <QString>
#include <iostream>

AddRecipe::AddRecipe(QWidget *parent, std::shared_ptr<RecipeStore> recipeStore) :
    QDialog(parent),
    ui(new Ui::AddRecipe),
    m_store (recipeStore)
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
    ui->choose_category->addItem(QString(Conversions::to_string(Category_Quick).c_str()));
    ui->choose_category->addItem(QString(Conversions::to_string(Category_Standard).c_str()));
    ui->choose_category->addItem(QString(Conversions::to_string(Category_Long).c_str()));

    ui->ingredient_choose_unit->addItem(QString(Conversions::to_string(UnitType_Number).c_str()));
    ui->ingredient_choose_unit->addItem(QString(Conversions::to_string(UnitType_Grammes).c_str()));
    ui->ingredient_choose_unit->addItem(QString(Conversions::to_string(UnitType_Liters).c_str()));
    ui->ingredient_choose_unit->addItem(QString(Conversions::to_string(UnitType_Mililiters).c_str()));
    ui->ingredient_choose_unit->addItem(QString(Conversions::to_string(UnitType_Cup).c_str()));
    ui->ingredient_choose_unit->addItem(QString(Conversions::to_string(UnitType_TeaSpoon).c_str()));
    ui->ingredient_choose_unit->addItem(QString(Conversions::to_string(UnitType_BigSpoon).c_str()));
}

void AddRecipe::clearAll()
{
    ui->edit_name->setText("");
    ui->edit_time->setText("");
    ui->edit_description->clear();
    ui->ingredient_edit_name->setText("");
    ui->ingredient_edit_quantity->setText("");
    ui->ingredientlist->clear();
    m_currentIngredients.clear();
}

void AddRecipe::on_buttonBox_accepted()
{
    try {
        addCurrentRecipeAndClear();
    } catch (std::invalid_argument e) {
        ViewUtils::showError(e.what());
    }
    catch (std::ios_base::failure f) {
        ViewUtils::showError(f.what());
    }
}

void AddRecipe::addCurrentRecipeAndClear()
{
    std::string name = ui->edit_name->text().toStdString();
    std::string description = ui->edit_description->toPlainText().toStdString();
    double time = Conversions::to_double(ui->edit_time->text().toStdString());
    Category cat = Conversions::to_category(ui->choose_category->currentText().toStdString());

    Recipe recipe(name, cat, description, time);
    for (auto &ing : m_currentIngredients)
        recipe.addIngredient(ing);

    m_store->addRecipe(recipe);
}

void AddRecipe::addCurrentIngredientAndClearIngredient()
{
    std::string name = ui->ingredient_edit_name->text().toStdString();
    double quantity = Conversions::to_double(ui->ingredient_edit_quantity->text().toStdString());
    UnitType unit = Conversions::to_unitType(ui->ingredient_choose_unit->currentText().toStdString());
    QString ingredientDescription;
    ingredientDescription += ui->ingredient_edit_quantity->text()
            + " " + Conversions::to_friendlyUnit(unit).c_str()
            + " " + name.c_str();
    ui->ingredientlist->addItem(ingredientDescription);

    m_currentIngredients.push_back(Ingredient(name, quantity, unit));

    ui->ingredient_edit_name->setText("");
    ui->ingredient_edit_quantity->setText("");
    ui->ingredient_choose_unit->setCurrentIndex(0);
}

void AddRecipe::on_ingredient_buttonadd_clicked()
{
    try {
        addCurrentIngredientAndClearIngredient();
    } catch (std::invalid_argument e) {
        ViewUtils::showError(e.what());
    }
}


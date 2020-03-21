#include "addrecipe.h"
#include "ui_addrecipe.h"

#include "core/conversions.h"
#include "core/recipe.h"

AddRecipe::AddRecipe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecipe)
{
    ui->setupUi(this);
}

AddRecipe::~AddRecipe()
{
    delete ui;
}

void AddRecipe::clearAll()
{
    ui->edit_name->setText("");
    ui->edit_time->setText("");
    ui->edit_description->clear();
    ui->ingredient_edit_name->setText("");
    ui->ingredient_edit_quantity->setText("");
    ui->ingredientlist->clear();
}

void AddRecipe::on_buttonBox_accepted()
{
    std::string name = ui->edit_name->text().toStdString();
    std::string description = ui->edit_description->toPlainText().toStdString();
    double time = Conversions::to_double(ui->edit_time->text().toStdString());
    Category cat = Conversions::to_category(ui->choose_category->currentText().toStdString());

    Recipe recipe(name, cat, description, time);

    // TODO fill ingredients
    m_store->addRecipe(recipe);
    // TODO save store (from main window?)
}

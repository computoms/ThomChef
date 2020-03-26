#include "shoppinglistview.h"
#include "ui_shoppinglistview.h"

ShoppingListView::ShoppingListView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShoppingListView)
{
    ui->setupUi(this);
}

ShoppingListView::~ShoppingListView()
{
    delete ui;
}

void ShoppingListView::setIngredients(std::vector<Ingredient> ingredients)
{
    m_ingredients = ingredients;
    ui->listIngredients->clear();
    for (auto &ing : m_ingredients)
        ui->listIngredients->addItem(ing.getFriendlyName().c_str());
}

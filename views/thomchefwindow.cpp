#include "thomchefwindow.h"
#include "ui_thomchefwindow.h"
#include "addrecipe.h"
#include "viewutils.h"

#include "core/filerecipestorage.h"
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
    try {
        m_store->initialize();
    } catch (std::ios_base::failure f) {
        ViewUtils::showError(f.what());
    }
}

void ThomChefWindow::on_button_addrecipe_clicked()
{
    AddRecipe *addRecipeView = new AddRecipe(this, m_store);
    addRecipeView->show();
}


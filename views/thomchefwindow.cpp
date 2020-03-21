#include "thomchefwindow.h"
#include "ui_thomchefwindow.h"

#include "core/filerecipestorage.h"

ThomChefWindow::ThomChefWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThomChefWindow)
{
    ui->setupUi(this);
    m_store = std::make_shared<RecipeStore>();
}

ThomChefWindow::~ThomChefWindow()
{
    delete ui;
}

void ThomChefWindow::initialize()
{
    m_store->initialize();
}

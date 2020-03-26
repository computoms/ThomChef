#include "filtersettingsview.h"
#include "ui_filtersettingsview.h"

FilterSettingsView::FilterSettingsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterSettingsView)
{
    ui->setupUi(this);
}

FilterSettingsView::~FilterSettingsView()
{
    delete ui;
}

void FilterSettingsView::init(const Configuration &config)
{
    m_defaultIngredients = config.getDefaultIngredients();
    for (const auto &ing : m_defaultIngredients)
        ui->listDefaultIngredients->addItem(ing.c_str());
    ui->button_addDefaultIngredient->setEnabled(false);
    ui->button_deleteDefaultIngredient->setEnabled(false);
}

std::vector<std::string> FilterSettingsView::getDefaultIngredients() const
{
    return m_defaultIngredients;
}

void FilterSettingsView::on_button_addDefaultIngredient_clicked()
{
    ui->listDefaultIngredients->addItem(ui->edit_defaultIngredient->text());
    m_defaultIngredients.push_back(ui->edit_defaultIngredient->text().toStdString());
    ui->edit_defaultIngredient->setText("");
}

void FilterSettingsView::on_button_deleteDefaultIngredient_clicked()
{
    std::string currentIng = ui->listDefaultIngredients->currentItem()->text().toStdString();
    for (auto it = m_defaultIngredients.begin(); it != m_defaultIngredients.end(); ++it)
    {
        if (*it == currentIng)
        {
            m_defaultIngredients.erase(it);
        }
    }

    ui->listDefaultIngredients->takeItem(ui->listDefaultIngredients->currentRow());
}

void FilterSettingsView::on_edit_defaultIngredient_textChanged(const QString &arg1)
{
    if (!ui->button_addDefaultIngredient->isEnabled() && arg1 != "")
        ui->button_addDefaultIngredient->setEnabled(true);
    else if (ui->button_addDefaultIngredient->isEnabled() && arg1 == "")
        ui->button_addDefaultIngredient->setEnabled(false);
}

void FilterSettingsView::on_edit_defaultIngredient_returnPressed()
{
    on_button_addDefaultIngredient_clicked();
}

void FilterSettingsView::on_listDefaultIngredients_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!ui->button_deleteDefaultIngredient->isEnabled() && current != nullptr)
        ui->button_deleteDefaultIngredient->setEnabled(true);
}

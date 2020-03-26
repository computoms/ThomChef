#include "shoppinglistview.h"
#include "ui_shoppinglistview.h"
#include "viewutils.h"
#include <QDate>
#include <QUrl>
#include <QDesktopServices>
#include <fstream>

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

void ShoppingListView::setDefaultEmailAddress(std::string emailAddress)
{
    ui->edit_email->setText(emailAddress.c_str());
}

std::string ShoppingListView::getEmailAddress() const
{
    return ui->edit_email->text().toStdString();
}

void ShoppingListView::sendByEmail(std::string emailAddress)
{
    std::string body = "";
    QDate date(QDate::currentDate());
    std::string dateS = "Liste des courses " + date.toString("dd/MM/yy").toStdString();

    for (auto &ing : m_ingredients)
        body += ing.getFriendlyName() + "\n";

    QString urlString = "mailto:";
    urlString += emailAddress.c_str();
    urlString += "?subject=";
    urlString += dateS.c_str();
    urlString += "&body=";
    urlString += body.c_str();
    QUrl url(urlString);
    QDesktopServices::openUrl(url);
}

// This unfortunately does not work anymore, due to a change in the Reminders app since OSX 10.14
void ShoppingListView::sendToReminders()
{
    std::string body("");
    body += "BEGIN:VCALENDAR\n";
    body += "VERSION:2.0\n";
    body += "PRODID:-//Computoms//Shopping List//EN\n";
    QDateTime now(QDateTime::currentDateTime());

    for (auto &ing : m_ingredients)
    {
        body += "BEGIN:VTODO\n";
        body += "DTSTAMP:" + now.toString("yyyyMMdd").toStdString() + "T" + now.toString("hhmmss").toStdString() + "Z" + "\n";
        body += "SEQUENCE:1\n";
        body += "STATUS:NEEDS-ACTION\n";
        body += "SUMMARY:" + ing.getName() + "\n";
        body += "DESCRIPTION:" + std::to_string(ing.getQuantity()) + ing.getUnit().friendlyName.c_str() + "\n";
        //texte += "PRIORITY:1\n";
        body += "END:VTODO\n";
    }
    body += "END:VCALENDAR\n";
    std::ofstream file((QCoreApplication::applicationDirPath().toStdString() + "/shoppingList.ics").c_str());
    file.write(body.c_str(),body.size());
    file.close();

    std::string command("open " + QCoreApplication::applicationDirPath().toStdString() + "/shoppingList.ics");
    system(command.c_str());
}

void ShoppingListView::on_button_sendEmail_clicked()
{
    std::string emailAddress = ui->edit_email->text().toStdString();
    sendByEmail(emailAddress);
}

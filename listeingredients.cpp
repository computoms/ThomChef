#include "listeingredients.h"
#include "ui_listeingredients.h"
#include "mainwindow.h"
#include <QDate>
#include <QUrl>
#include <QDesktopServices>
#include <QMessageBox>

/*ListeIngredients::ListeIngredients(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListeIngredients)
{
    ui->setupUi(this);
}*/

ListeIngredients::ListeIngredients(MainWindow* mWin): ui(new Ui::ListeIngredients)
{
    ui->setupUi(this);
    sources = mWin->getSources();
}

ListeIngredients::~ListeIngredients()
{
    delete ui;
}

void ListeIngredients::affiche(std::vector<Plat> recs)
{
    recettes = recs;
    std::string txt("");
    for(int i(0);i<recs.size();++i)
    {
        if(recs[i].size()>0)
        {
                txt += "\n";
                for(int j(0);j<recs[i].size();++j)
                {
                    if(j!=0)
                        txt += " / ";
                    txt += recs[i][j]->getNom();
                }
                txt += "\n";
                for(int j(0);j<recs[i].size();++j)
                {
                    if(!recs[i][j]->getCongel())
                    {
                        for(int k(0);k<recs[i][j]->getTableauIngredients().size();++k)
                        {
                            txt += "    - " + recs[i][j]->getTableauIngredients()[k] + "\n";
                        }
                    }
                }
                txt += "\n";
        }
    }
    ui->label_2->setText(QString(txt.c_str()));
}

void ListeIngredients::on_pushButton_clicked()
{
    std::string txt(ui->label_2->text().toStdString());
    QDate date(QDate::currentDate());
    std::string dateS = "Liste des courses - " + date.toString("dd/MM/yy").toStdString();

    QString urlString = "mailto:";
    urlString += "thomas.b3ck@gmail.com";
    urlString += "?subject=";
    urlString += dateS.c_str();
    urlString += "&body=";
    urlString += txt.c_str();
    QUrl url(urlString);
    QDesktopServices::openUrl(url);
    this->hide();
}

void ListeIngredients::on_pushButton_2_clicked()
{
    std::string texte("");
    texte += "BEGIN:VCALENDAR\n";
    texte += "VERSION:2.0\n";
    texte += "PRODID:-//Thomas Beck Corp//Liste de courses//FR\n";
    QDateTime now(QDateTime::currentDateTime());

    for(int i(0);i<recettes.size();++i)
    {
        for(int j(0); j<recettes[i].size();++j)
        {
            for(int k(0);k<recettes[i][j]->getTableauIngredients().size();++k)
            {
                texte += "BEGIN:VTODO\n";
                texte += "DTSTAMP:" + now.toString("yyyyMMdd").toStdString() + "T" + now.toString("hhmmss").toStdString() + "Z" + "\n";
                texte += "SEQUENCE:1\n";
                texte += "STATUS:NEEDS-ACTION\n";
                texte += "SUMMARY:" + recettes[i][j]->getTableauIngredients()[k] + "\n";
                texte += "DESCRIPTION:" + recettes[i][j]->getNom() + "\n";
                //texte += "PRIORITY:1\n";
                texte += "END:VTODO\n";
            }
        }
    }
    texte += "END:VCALENDAR\n";
    ofstream file((QCoreApplication::applicationDirPath().toStdString() + "/listeCourses.ics").c_str());
    file.write(texte.c_str(),texte.size());
    file.close();

    std::string command("open " + QCoreApplication::applicationDirPath().toStdString() + "/listeCourses.ics");
    system(command.c_str());
    this->hide();
}

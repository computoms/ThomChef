#include "ajouterrecette.h"
#include "ui_ajouterrecette.h"
#include "mainwindow.h"
#include <fstream>
#include <string>
#include <QMessageBox>
#include <QDateTime>

/*AjouterRecette::AjouterRecette(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AjouterRecette)
{
    ui->setupUi(this);
    //sources = main->getSources();
    ajout = true;
}*/
AjouterRecette::AjouterRecette(MainWindow* mWin): ui(new Ui::AjouterRecette)
{
    ui->setupUi(this);
    main = mWin;
    sources = main->getSources();
    ajout = true;
    ui->lineNom_2->setFocus();
    nom = "";
}

void AjouterRecette::actualiser()
{
    ui->lineNom_2->setText("");
    ui->lineIngredient1_2->setText("");
    ui->lineIngredient2_2->setText("");
    ui->lineIngredient3_2->setText("");
    ui->lineIngredient4_2->setText("");
    ui->lineIngredient5_2->setText("");
    ui->plainTextEdit_2->setPlainText("");
    ui->listWidget_2->clear();
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->lineNom_2->setFocus();
    ui->checkBox->setChecked(false);

    for(int i(0);i<sources->getNOMS_CATEGORIES().size();++i)
    {
        ui->comboBox->addItem(QString(sources->getNOMS_CATEGORIES()[i].c_str()));
    }
    ui->comboBox_2->addItem("Rapide");
    ui->comboBox_2->addItem("Long");
}

AjouterRecette::~AjouterRecette()
{
    delete ui;
}
void AjouterRecette::on_boutonAjouterIngredient_2_clicked()
{
    if(ui->lineIngredient1_2->text() != QString(""))
        ui->listWidget_2->addItem(ui->lineIngredient1_2->text());
    if(ui->lineIngredient2_2->text() != QString(""))
        ui->listWidget_2->addItem(ui->lineIngredient2_2->text());
    if(ui->lineIngredient3_2->text() != QString(""))
        ui->listWidget_2->addItem(ui->lineIngredient3_2->text());
    if(ui->lineIngredient4_2->text() != QString(""))
        ui->listWidget_2->addItem(ui->lineIngredient4_2->text());
    if(ui->lineIngredient5_2->text() != QString(""))
        ui->listWidget_2->addItem(ui->lineIngredient5_2->text());

    ui->lineIngredient1_2->setText("");
    ui->lineIngredient2_2->setText("");
    ui->lineIngredient3_2->setText("");
    ui->lineIngredient4_2->setText("");
    ui->lineIngredient5_2->setText("");
}

void AjouterRecette::on_boutonAjouter_2_clicked()
{

    string no("");
    int categorie(0);
    string description("");
    std::vector<string> ingredients;
    bool congel;

    no = ui->lineNom_2->text().toStdString();
    description = ui->plainTextEdit_2->toPlainText().toStdString();
    categorie = ui->comboBox->currentIndex();
    congel = ui->checkBox->isChecked();

    // Remplir les ingredients...
    for(int i(0);i<ui->listWidget_2->count();++i)
    {
        ingredients.push_back(ui->listWidget_2->item(i)->text().toStdString());
    }

    Recette* rec = new Recette(no, categorie, description, ingredients, congel);
    rec->setTemps(ui->comboBox_2->currentIndex());
    rec->setNombreRepas(ui->spinBox->value());
    if(congel)
    {
        QDateTime today(QDateTime::currentDateTime());
        std::string todayS(today.toString("dd/MM/yyyy hh:mm:ss").toStdString());
        rec->setDateCongel(todayS);
    }

    if(ajout)
    {
        bool doublon(false);
        doublon = sources->findDoublon(rec->getNom());
        if(!doublon)
        {
            sources->addRecette(rec);

            main->actualiser();
            this->close();
        }
        else
        {
            QMessageBox::critical(this, "Erreur du nom", "La recette à ajouter possède le même nom qu'une recette déjà existante");
        }

    }
    else
    {
        sources->modifierRecette(rec, nom);
        ajout = true;
        ui->boutonAjouter_2->setText("Ajouter");

        main->actualiser();
        this->close();
    }
}

void AjouterRecette::modifierRecette(Recette* rec)
{
    ui->lineNom_2->setText(QString(rec->getNom().c_str()));
    ui->lineIngredient1_2->setText("");
    ui->lineIngredient2_2->setText("");
    ui->lineIngredient3_2->setText("");
    ui->lineIngredient4_2->setText("");
    ui->lineIngredient5_2->setText("");
    ui->plainTextEdit_2->setPlainText(QString(rec->getDescription().c_str()));
    ui->boutonAjouter_2->setText("Modifier");
    ui->listWidget_2->clear();
    for(int i(0);i<rec->getTableauIngredients().size();++i)
    {
        ui->listWidget_2->addItem(new QListWidgetItem(QString(rec->getTableauIngredients()[i].c_str())));
    }

    ui->checkBox->setChecked(rec->getCongel());
    ui->comboBox->setCurrentIndex(rec->getCategorie());
    ui->comboBox_2->setCurrentIndex(rec->getTemps());
    ui->spinBox->setValue(rec->getNombreRepas());
    ajout = false;
    nom = rec->getNom();
}


void AjouterRecette::on_comboBox_currentIndexChanged(int index)
{

}

void AjouterRecette::on_listWidget_2_clicked()
{
    ui->pushButton->setEnabled(true);
}

void AjouterRecette::on_pushButton_clicked(bool checked)
{
    QList<QListWidgetItem*> list(ui->listWidget_2->selectedItems());
    if(list.size()>0)
    {
        QList<QListWidgetItem*> theList;
        for(int i(0);i<ui->listWidget_2->count();++i)
        {
            if(ui->listWidget_2->item(i)->text() != list[0]->text())
            {
                theList.push_back(new QListWidgetItem(ui->listWidget_2->item(i)->text()));
            }
        }
        ui->listWidget_2->clear();
        for(int i(0);i<theList.size();++i)
        {
            ui->listWidget_2->addItem(theList[i]);
        }
    }
}

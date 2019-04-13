#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDate>
#include <QMessageBox>
#include <QObject>

// TODO
// BUG Fixes
// - When a double entry appears in the generated side, it changes both entries and should not
// - When you click on a generated item: it should show the description
// IMPROVEMENTS
// - Show a "summary" of all the dishes and how many meals it's for, the recipe...
// - Possibility to assign a day for a dish for the summary

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), itemCongelSelectionne(""), currentDateGeneration(-1)
{
    ui->setupUi(this);
    sources = new Data();
    listeIngred = new ListeIngredients(this);
    ajout = new AjouterRecette(this);
    gererConfig = new GererConfiguration();
    init();

    // Dates de péramptions :
    std::vector<std::vector<Recette*> > rec(sources->getRecettes());
    std::vector<std::string> message;
    for(unsigned int i(0);i<rec.size();++i)
    {
        for(unsigned int j(0);j<rec[i].size();++j)
        {
            if(rec[i][j]->getCongel())
            {
                QDate auj(QDate::currentDate());
                QDate theDate(QDate::fromString(QString(rec[i][j]->getDateCongel().substr(0,10).c_str()), "dd/MM/yyyy"));
                theDate = theDate.addDays(305);
                if(auj > theDate)
                {
                    message.push_back(rec[i][j]->getNom() + "\n");
                }
            }
        }
    }
    QString texte("Les éléments \n\n");
    for(unsigned int i(0);i<message.size();++i)
    {
        texte += QString(message[i].c_str());
    }
    texte += "\n\nsont dans le congélateur depuis 305 jours et il vaudrait mieux les manger avant qu'ils ne se périment dans 60 jours...";
    if(message.size()>0)
    {
        QMessageBox::information(this,"Dates de péremption - congélateur", texte);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sources;
    //delete liste;
    delete ajout;
    delete gererConfig;
    delete listeIngred;
}

void MainWindow::init()
{
    sources->init();
    ui->spinBox->setValue(5);
    ui->spinBox_2->setValue(4);
    initCongelateur();
    initGeneration(currentDateGeneration);
    initAffichage();
    ajout->actualiser();
}

void MainWindow::initCongelateur()
{
    ui->listWidget->clear();
    ui->listWidget_4->clear();
    // Congélateur
    std::vector<std::vector<Recette*> > rec(sources->getRecettes());

    for(unsigned int i(0);i<rec.size();++i)
    {
        for(unsigned int j(0);j<rec[i].size();++j)
        {
            if(rec[i][j]->getCongel())
            {
                QListWidgetItem* newit = new QListWidgetItem();
                newit->setText(QString(rec[i][j]->getNom().c_str()));
                ui->listWidget->addItem(newit);
            }
            if(rec[i][j]->getARetirer())
            {
                QListWidgetItem* newit = new QListWidgetItem();
                newit->setText(QString(rec[i][j]->getNom().c_str()));
                ui->listWidget_4->addItem(newit);
            }
        }
    }
}

void MainWindow::initAffichage()
{
    // Affichage des recettes
    std::vector<std::vector<Recette*> > rec(sources->getRecettes());

    ui->listWidget_3->clear();
    ui->pushButton_modifier->setEnabled(false);
    ui->pushButton_supprimer->setEnabled(false);

    for(unsigned int i(0);i<rec.size();++i)
    {
        for(unsigned int j(0);j<rec[i].size();++j)
        {
            QListWidgetItem* newit = new QListWidgetItem();
            newit->setText(QString(rec[i][j]->getNom().c_str()));
            ui->listWidget_3->addItem(newit);
        }
    }
}

void MainWindow::initGeneration(int indice)
{
    ui->listWidget_2->clear();
    if(sources->getRecGeneree().size() > 0)
    {
        if(indice < 0 or indice>=sources->getDatesGeneree().size())
        {
            indice = sources->getRecGeneree().size()-1;
        }

        unsigned int compteurRepas(0);
        std::vector<Plat> recGeneree((sources->getRecGeneree())[indice]);
        for(unsigned int i(0);i<recGeneree.size();++i)
        {
            if(recGeneree[i].size()>0)
            {
                if(recGeneree[i][0]->getTemps()==RAPIDE)
                {
                    QListWidgetItem* newit = new QListWidgetItem();
                    std::string txt("");
                    for(int j(0);j<recGeneree[i].size();++j)
                    {
                        if(j!=0)
                            txt += " / ";
                        txt += recGeneree[i][j]->getNom();
                    }
                    newit->setText(QString(txt.c_str()));
                    ui->listWidget_2->addItem(newit);
                    compteurRepas += recGeneree[i][0]->getNombreRepas();
                }
            }
        }
        for(unsigned int i(0);i<recGeneree.size();++i)
        {
            if(recGeneree[i].size()>0)
            {
                if(recGeneree[i][0]->getTemps()==LONG)
                {
                    QListWidgetItem* newit = new QListWidgetItem();
                    std::string txt("");
                    for(int j(0);j<recGeneree[i].size();++j)
                    {
                        if(j!=0)
                            txt += " / ";
                        txt += recGeneree[i][j]->getNom();
                    }
                    newit->setText(QString(txt.c_str()));
                    ui->listWidget_2->addItem(newit);
                    compteurRepas += recGeneree[i][0]->getNombreRepas();
                }
            }
        }

        QString date(("Date : " + sources->getDatesGeneree()[indice]).c_str());
        ui->label_date->setText(date);
        if(indice>0)
        {
            ui->pushButton_previous->setEnabled(true);
        }
        currentDateGeneration = indice;

        ui->label_14->setText(QString(("Plats pour : " + sources->intToString(compteurRepas) + " repas.").c_str()));
    }
}

void MainWindow::updateAll()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    init();
    //liste->actualiser();
    ajout->actualiser();
}

void MainWindow::actualiser()
{
    if(currentDateGeneration>0)
    {
        ui->pushButton_previous->setEnabled(true);
    }
    else
    {
        ui->pushButton_previous->setEnabled(false);
    }
    if(currentDateGeneration<(sources->getDatesGeneree().size()-1))
    {
        ui->pushButton_next->setEnabled(true);
    }
    else
    {
        ui->pushButton_next->setEnabled(false);
    }
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    init();
}

void MainWindow::generer(int nbrRapides, int nbrLongues)
{
    ui->listWidget_2->clear();
    std::vector<Plat> rand(sources->randomdays(nbrRapides, nbrLongues));
    std::vector<Plat> listeRec;
    std::vector<Recette*> listeARetirer;
    for(unsigned int i(0);i<rand.size();++i)
    {
        std::string txt("");
        for(unsigned int j(0);j<rand[i].size();++j)
        {
            if(j!=0)
                txt += " / ";
            txt += rand[i][j]->getNom();
            if(rand[i][j]->getCongel())
            {
                listeARetirer.push_back(rand[i][j]);
            }
        }
        ui->listWidget_2->addItem(new QListWidgetItem(QString(txt.c_str())));
        listeRec.push_back(rand[i]);
    }

    for(int i(0);i<listeARetirer.size();++i)
    {
        listeARetirer[i]->setARetirer(true);
    }
    sources->updateFile();

    QDateTime auj(QDateTime::currentDateTime());
    std::string now(auj.toString("dd/MM/yyyy hh:mm:ss").toStdString());
    sources->ajouterGeneration(now, listeRec);
    ++currentDateGeneration;
    supprimerGenerationPrecedentes();
    actualiser();
}

void MainWindow::supprimerGenerationPrecedentes()
{
    vector<string> datesPrev(sources->getDatesGeneree());
    vector<int> aSupprimer;

    QDateTime auj(QDateTime::currentDateTime());

    for(unsigned int i(0);i<datesPrev.size()-1;++i)
    {
        QDateTime theDate(QDateTime::fromString(QString(datesPrev[i].c_str()), "dd/MM/yyyy hh:mm:ss"));
        QDateTime theDate2 = theDate.addDays(30);
        QDateTime theDate3 = theDate.addSecs(3600);
        if(auj > theDate2 or auj < theDate3)
        {
            aSupprimer.push_back(i);
        }

    }
    sources->supprimerGeneration(aSupprimer);
}

void MainWindow::modifierRecette(Recette* rec)
{
    ajout->modifierRecette(rec);
    ajout->show();
}

Data* MainWindow::getSources()
{
    return sources;
}


void MainWindow::on_pushButton_clicked()
{
    int nbrRapides(ui->spinBox->value());
    int nbrLongues(ui->spinBox_2->value());
    vector<string> datesPrev(sources->getDatesGeneree());
    bool message(false);
    QDateTime auj(QDateTime::currentDateTime());

    for(unsigned int i(0);i<datesPrev.size()
        ;++i)
    {
        QDateTime theDate(QDateTime::fromString(QString(datesPrev[i].c_str()), "dd/MM/yyyy hh:mm:ss"));
        QDateTime theDate3 = theDate.addSecs(3600);
        if(auj < theDate3)
        {
            message = true;
        }
    }
    if(message)
    {
        QMessageBox msgBox;
         msgBox.setText("Auto-suppression.");
         msgBox.setFixedWidth(300);
         msgBox.setInformativeText("Attention, l'auto-suppression est activée.\nVoulez-vous vraiment générer à nouveau ?");
         msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
         msgBox.setDefaultButton(QMessageBox::Yes);
         msgBox.setIcon(QMessageBox::Question);
         int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
        {
            generer(nbrRapides, nbrLongues);
        }
    }
    else
    {
        generer(nbrRapides, nbrLongues);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ajout->actualiser();
    ajout->show();
}


void MainWindow::on_listWidget_clicked(QModelIndex)
{
    ui->pushButton_enlever->setEnabled(true);
    QList<QListWidgetItem*> list(ui->listWidget->selectedItems());
    if(list.size()>0)
    {
        std::string date(sources->findRecette(list[0]->text().toStdString())->getDateCongel());
        QString Qdate(("Mis le : " + date).c_str());
        if(date.size()>9)
        {
            Qdate = ("Mis le : " + date.substr(0,6) + date.substr(8,2)).c_str();
        }
        ui->label_9->setText(Qdate);
    }
}

void MainWindow::on_actionAfficher_la_configuration_triggered()
{
    gererConfig->init(sources);
    gererConfig->show();
}

void MainWindow::on_listWidget_2_clicked(QModelIndex)
{
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
    afficheBonneRecette();
}


void MainWindow::afficheBonneRecette()
{
    /*QList<QListWidgetItem*> list(ui->listWidget_2->selectedItems());
    for(unsigned int i(0);i<list.size();++i)
    {
        selectionneRecette(sources->findRecette(list[i]->text().toStdString()));
    }*/
}

void MainWindow::on_pushButton_enlever_clicked()
{
    QList<QListWidgetItem*> list(ui->listWidget->selectedItems());
    for(unsigned int i(0);i<list.size();++i)
    {
        //std::string nom(elementSelectionne.toString().toStdString());
        std::string nom(list[i]->text().toStdString());
        Recette* rec = sources->findRecette(nom);
        rec->setCongel(false);
    }

    sources->updateFile();
    updateAll();
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    QItemSelectionModel *selection = ui->listWidget->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    QVariant elementSelectionne = ui->listWidget->model()->data(indexElementSelectionne, Qt::DisplayRole);

    std::string nom(elementSelectionne.toString().toStdString());

    // Recherche de la recette correspondante
    Recette* rec = sources->findRecette(nom);

    //actualiser();
    selectionneRecette(rec);
    //liste->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    QList<QListWidgetItem*> list(ui->listWidget_2->selectedItems());

    for(int k(0);k<list.size();++k)
    {
        std::string nom(list[k]->text().toStdString());
        // Recherche de la recette correspondante
        Recette* rec = sources->findRecette(nom.substr(0,nom.find("/")));

        Plat rec2;
        if(rec->getTemps()==RAPIDE)
        {
            rec2 = sources->random1day(RAPIDE);
        }
        else
        {
            rec2 = sources->random1day(LONG);
        }

        // remplacer le texte de l'item correspondant :
        for(unsigned int i(0);i<ui->listWidget_2->count();++i)
        {
            if(ui->listWidget_2->item(i)->text().toStdString() == nom)
            {
                std::string st("");
                for(int j(0);j<rec2.size();++j)
                {
                    if(j!=0)
                        st += " / ";
                    st += rec2[j]->getNom();
                }
                ui->listWidget_2->item(i)->setText(QString(st.c_str()));
                sources->modifierGeneration(currentDateGeneration, nom, rec2);
            }
        }
    }
}

void MainWindow::on_pushButton_liste_clicked()
{
    std::vector<Plat> generationCourante(sources->getRecGeneree()[sources->getRecGeneree().size()-1]);
    listeIngred->affiche(generationCourante);
    listeIngred->show();
}

void MainWindow::on_pushButton_previous_clicked()
{
    initGeneration(currentDateGeneration-1);
    actualiser();
}

void MainWindow::on_pushButton_next_clicked()
{
    initGeneration(currentDateGeneration+1);
    actualiser();
}

void MainWindow::on_pushButton_6_clicked()
{
    sources->supprimerGeneration(currentDateGeneration);
    actualiser();
}

void MainWindow::on_pushButton_7_clicked()
{
    QList<QListWidgetItem*> list(ui->listWidget_2->selectedItems());
    for(unsigned int i(0);i<list.size();++i)
    {
        QString nom(list[i]->text());
        QStringList noms;
        noms = nom.split(" / ", QString::SkipEmptyParts);

        for(int i(0);i<noms.size();++i)
        {
            QMessageBox::information(0, "info", noms[i]);
        }

        sources->supprimerRecGeneration(noms, currentDateGeneration);
    }
    actualiser();
}

int MainWindow::getCurrentDateIndex()
{
    return currentDateGeneration;
}





/*
 * Affichage des recettes
 *
 */


void MainWindow::selectionneRecette(Recette* rec)
{
    // Sélectionner le bon plat.
    QListWidgetItem* it;
    bool ok(false);
    for(unsigned int i(0);i<ui->listWidget_3->count();++i)
    {
        if(ui->listWidget_3->item(i)->text().toStdString() == rec->getNom())
        {
            it = ui->listWidget_3->item(i);
            ok = true;
        }
    }
    if(ok)
    {
        ui->listWidget_3->setCurrentItem(it);
        QItemSelectionModel *selection = ui->listWidget_3->selectionModel();
        QModelIndex indexElementSelectionne = selection->currentIndex();
        on_listWidget_3_clicked(indexElementSelectionne);
    }
}

void MainWindow::on_listWidget_3_clicked(QModelIndex)
{
    ui->pushButton_modifier->setEnabled(true);
    ui->pushButton_supprimer->setEnabled(true);
    ui->checkBox->setEnabled(true);

    QList<QListWidgetItem*> list(ui->listWidget_3->selectedItems());
    if(list.size()>0)
    {
        std::string nom(list[0]->text().toStdString());
        ui->label_nom->setText(QString(nom.c_str()));

        // Recherche de la recette correspondante
        Recette* rec = sources->findRecette(nom);

        ui->label_5->setText(QString(rec->getIngredients().c_str()));
        ui->label_6->setText(QString(rec->getDescription().c_str()));
        std::string surge("");
        if(rec->getTemps() == RAPIDE)
        {
            surge += " (Rapide)";
        }
        else
        {
            surge += " (Long)";
        }

        ui->label_categorie->setText(QString((sources->getNOMS_CATEGORIES()[rec->getCategorie()] + surge).c_str()));

        if(rec->getCongel())
        {
            ui->checkBox->setChecked(true);
        }
        else
        {
            ui->checkBox->setChecked(false);
        }

        ui->label_nombre->setText(QString((sources->intToString(rec->getNombreRepas()) + " repas.").c_str()));
    }
}





void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        // La mettre au congel...
        QList<QListWidgetItem*> list(ui->listWidget_3->selectedItems());
        for(unsigned int i(0);i<list.size();++i)
        {
            Recette* rec(sources->findRecette(list[i]->text().toStdString()));
            rec->setCongel(true);
            // Date de mise en congel
            QDateTime today(QDateTime::currentDateTime());
            std::string todayS(today.toString("dd/MM/yyyy hh:mm:ss").toStdString());
            rec->setDateCongel(todayS);
        }
    }
    else
    {
        // Enlever du congel (si elle est au congel)
        QList<QListWidgetItem*> list(ui->listWidget_3->selectedItems());
        for(unsigned int i(0);i<list.size();++i)
        {
            Recette* rec(sources->findRecette(list[i]->text().toStdString()));
            rec->setCongel(false);
            rec->setARetirer(false);
            rec->setDateCongel("0");
        }
    }
    sources->updateFile();
    actualiser();
}


void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    QString nom(ui->lineEdit->text());
    //nom = nom.toUpper();
    std::vector<Recette*> recs = sources->findRecettePartial(nom.toStdString());
    ui->listWidget_3->clear();
    for(unsigned int i(0);i<recs.size();++i)
    {
        QListWidgetItem* newit = new QListWidgetItem();
        newit->setText(QString(recs[i]->getNom().c_str()));
        ui->listWidget_3->addItem(newit);
    }
}


void MainWindow::on_pushButton_modifier_clicked()
{
    QList<QListWidgetItem*> list(ui->listWidget_3->selectedItems());
    for(unsigned int i(0);i<list.size();++i)
    {
        //sources->modifierRecette(sources->findRecette(list[i]->text().toStdString()));
        ajout->modifierRecette(sources->findRecette(list[i]->text().toStdString()));
        ajout->show();
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    QList<QListWidgetItem*> list(ui->listWidget_3->selectedItems());
    for(unsigned int i(0);i<list.size();++i)
    {
        sources->supprimerRecette(list[i]->text().toStdString());
    }
    actualiser();
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    QList<QListWidgetItem*> list(ui->listWidget_3->selectedItems());
    Plat pt;
    for(int i(0);i<list.size();++i)
    {
        pt.push_back(sources->findRecette(list[i]->text().toStdString()));
    }
    sources->ajouterRecGeneration(currentDateGeneration, pt);
    actualiser();
}



void MainWindow::on_pushButton_4_clicked()
{
    QList<QListWidgetItem*> list(ui->listWidget_4->selectedItems());
    for(unsigned int i(0);i<list.size();++i)
    {
        //std::string nom(elementSelectionne.toString().toStdString());
        std::string nom(list[i]->text().toStdString());
        Recette* rec = sources->findRecette(nom);
        rec->setARetirer(false);
        rec->setCongel(false);
    }

    sources->updateFile();
    actualiser();
}

void MainWindow::on_pushButton_3_clicked()
{
    QList<QListWidgetItem*> list(ui->listWidget_4->selectedItems());
    for(unsigned int i(0);i<list.size();++i)
    {
        //std::string nom(elementSelectionne.toString().toStdString());
        std::string nom(list[i]->text().toStdString());
        Recette* rec = sources->findRecette(nom);
        rec->setARetirer(false);
    }

    sources->updateFile();
    actualiser();
}

void MainWindow::on_listWidget_4_clicked(const QModelIndex &index)
{
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
}

void MainWindow::on_actionQuiter_triggered()
{
    this->close();
}

void MainWindow::on_toolButton_clicked()
{
    on_pushButton_liste_clicked();
    listeIngred->hide();
    listeIngred->on_pushButton_2_clicked();
}

void MainWindow::on_listWidget_3_pressed(const QModelIndex &index)
{
}

void MainWindow::on_listWidget_3_currentRowChanged(int currentRow)
{
    on_listWidget_3_clicked(ui->listWidget_3->currentIndex());
}

void MainWindow::on_listWidget_2_currentRowChanged(int currentRow)
{
    on_listWidget_2_clicked(ui->listWidget_2->currentIndex());
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    on_listWidget_clicked(ui->listWidget->currentIndex());
}

void MainWindow::on_toolButton_2_clicked()
{
    std::string texte("");
    texte += "BEGIN:VCALENDAR\n";
    texte += "VERSION:2.0\n";
    texte += "PRODID:-//Thomas Beck Corp//Liste de courses//FR\n";
    QDateTime now(QDateTime::currentDateTime());

   // for(unsigned int i(0);i<sources->getRecGeneree().size();++i)
    {
        for(unsigned int j(0); j<ui->listWidget_2->count();++j)
        {
            texte += "BEGIN:VTODO\n";
            texte += "DTSTAMP:" + now.toString("yyyyMMdd").toStdString() + "T" + now.toString("hhmmss").toStdString() + "Z" + "\n";
            texte += "SEQUENCE:1\n";
            texte += "STATUS:NEEDS-ACTION\n";
            texte += "SUMMARY:";
            for(int k(0);k<sources->getRecGeneree()[sources->getRecGeneree().size()-1][j].size();++k)
            {
                if(k!=0)
                    texte += " / ";
                texte += sources->getRecGeneree()[sources->getRecGeneree().size()-1][j][k]->getNom();
            }
            if(sources->getRecGeneree()[sources->getRecGeneree().size()-1][j][0]->getTemps() == RAPIDE)
            {
                texte += " (Rapide)\n";
            }
            else
            {
                texte += " (Long)\n";
            }
            //texte += "DESCRIPTION:" + recs[i]->getNom() + "\n";
            //texte += "PRIORITY:1\n";
            texte += "END:VTODO\n";
        }
    }
    texte += "END:VCALENDAR\n";


    ofstream file((QCoreApplication::applicationDirPath().toStdString() + "/listeRepas.ics").c_str());
    file.write(texte.c_str(),texte.size());
    file.close();


    system(("open " + QCoreApplication::applicationDirPath().toStdString() + "/listeRepas.ics").c_str());
}

void MainWindow::on_listWidget_3_doubleClicked(const QModelIndex &index)
{
    on_pushButton_modifier_clicked();
}


void MainWindow::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->isChecked())
    {
        sources->setEviterDoublons(true);
    }
    else
    {
        sources->setEviterDoublons(false);
    }
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include "data.h"
#include "ajouterrecette.h"
#include "gererconfiguration.h"
#include "listeingredients.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init();
    void initCongelateur();
    void initGeneration(int indice = -1);
    void initAffichage();
    void updateAll();
    void actualiser();
    void generer(int nbrRapides, int nbrLongues);
    void supprimerGenerationPrecedentes();
    void modifierRecette(Recette* rec);

    Data* getSources();
    int getCurrentDateIndex();

    // Affichage des recettes
    void selectionneRecette(Recette* rec);
    void afficheBonneRecette();


public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    //void on_pushButton_3_clicked();
    void on_listWidget_clicked(QModelIndex);
    void on_actionAfficher_la_configuration_triggered();
    void on_listWidget_2_clicked(QModelIndex);

    //Affichage des recettes
    //void on_listWidget_3_clicked(QModelIndex);
    void on_checkBox_clicked();
    
private slots:

    void on_pushButton_enlever_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_pushButton_5_clicked();


    void on_pushButton_liste_clicked();

    void on_pushButton_previous_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    //Affichage des recettes
    void on_lineEdit_textEdited(const QString &arg1);

    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_ajouter_clicked();

    void on_listWidget_3_clicked(QModelIndex);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_listWidget_4_clicked(const QModelIndex &index);


    void on_actionQuiter_triggered();

    void on_toolButton_clicked();

    void on_listWidget_3_pressed(const QModelIndex &index);

    void on_listWidget_3_currentRowChanged(int currentRow);

    void on_listWidget_2_currentRowChanged(int currentRow);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_toolButton_2_clicked();

    void on_listWidget_3_doubleClicked(const QModelIndex &index);

    void on_checkBox_2_clicked();

private:
    Ui::MainWindow *ui;
    Data* sources;

    //ListePlats* liste;
    AjouterRecette* ajout;
    GererConfiguration* gererConfig;
    ListeIngredients* listeIngred;

    std::string itemCongelSelectionne;
    int currentDateGeneration;
};

#endif // MAINWINDOW_H

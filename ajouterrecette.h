#ifndef AJOUTERRECETTE_H
#define AJOUTERRECETTE_H

#include <QWidget>
#include <string>
#include "data.h"

class MainWindow;

namespace Ui {
class AjouterRecette;
}

class AjouterRecette : public QWidget
{
    Q_OBJECT

public:
    //explicit AjouterRecette(QWidget *parent = 0);
    AjouterRecette(MainWindow* mWin);
    ~AjouterRecette();
    void actualiser();
    void modifierRecette(Recette* rec);

public slots:
    void on_boutonAjouter_2_clicked();
    void on_boutonAjouterIngredient_2_clicked();

signals:
    void hiddenFen();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_listWidget_2_clicked();

    void on_pushButton_clicked(bool checked);

private:
    Ui::AjouterRecette *ui;
    Data* sources;
    MainWindow* main;
    bool ajout;
    std::string nom;
};

#endif // AJOUTERRECETTE_H

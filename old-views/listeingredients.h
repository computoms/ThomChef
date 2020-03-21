#ifndef LISTEINGREDIENTS_H
#define LISTEINGREDIENTS_H

#include <QWidget>
#include "data.h"

class MainWindow;

namespace Ui {
class ListeIngredients;
}

class ListeIngredients : public QWidget
{
    Q_OBJECT
    
public:
    //explicit ListeIngredients(QWidget *parent = 0);
    ListeIngredients(MainWindow* mWin);
    ~ListeIngredients();

    void affiche(std::vector<Plat> recs);
    
public slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ListeIngredients *ui;
    Data* sources;
    std::vector<Plat> recettes;
};

#endif // LISTEINGREDIENTS_H

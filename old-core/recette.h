#ifndef RECETTE_H
#define RECETTE_H

#include <string>
#include <vector>
#include "XMLParser.h"

using namespace std;

enum {RAPIDE,LONG};
enum {FECULENT,LEGUME,VIANDE,AUTRE};

class Recette
{
public:
    Recette();
    Recette(Item* it);
    Recette(std::string nomR, int catR, std::string descR, vector<std::string> ingredientsR, bool congelR);

    string getNom();
    int getCategorie();
    int getTemps();
    string getDescription();
    string getIngredients();
    std::vector<std::string> getTableauIngredients();
    bool getCongel();
    bool getARetirer();
    string getDateCongel();
    unsigned int getNombreRepas();
    void setNom(string n);
    void setCategorie(int c);
    void setTemps(int t);
    void setDescription(string desc);
    void setTableauIngredients(vector<string> ing);
    void setCongel(bool value);
    void setARetirer(bool value);
    void setDateCongel(string date);
    void setNombreRepas(unsigned int nb);
    bool stringToBool(string laString);
    int stringToInt(string laString);

private:
    string nom;
    int categorie;
    int temps;
    string description;
    vector<string> ingredients;
    bool congel;
    bool aRetirer;
    string dateCongel;
    unsigned int nbRepas;
};

#endif // RECETTE_H

#ifndef DATA_H
#define DATA_H

#include "XMLParser.h"
#include "recette.h"
#include <QDir>

typedef std::vector<Recette*> Plat;

class Data
{
public:
    Data();
    ~Data();
    void init();
    vector<Plat> randomdays(int nbrRapide, int nbrLongues);
    Plat random1day(unsigned int temps);
    Plat random1day(std::vector<std::vector<Recette*> > const& recs);
    int randomNum(int size);


    void ajouterARetirer(Recette *rec);
    void ajouterGeneration(std::string date, std::vector<Plat> plats);
    void ajouterRecGeneration(int date, Plat pt);
    void supprimerGeneration(int indice);
    void supprimerGeneration(std::vector<int> indice);
    void addRecette(Recette* rec);
    void modifierRecette(Recette* rec, string formerNom);
    void modifierGeneration(int numDate, string nom, Plat newPlat);
    void supprimerRecette(std::string nomRec);
    void supprimerRecGeneration(QStringList noms, int date);


    int stringToInt(std::string s);
    std::string intToString(int i);
    bool findDoublon(std::string n);
    Recette* findRecette(std::string name);
    std::vector<Recette *> findRecettePartial(std::string name);
    void updateFile();
    void updateConfig();
    void updateGeneree();


    std::vector<std::vector<Recette*> > getRecettes();
    std::vector<std::vector<Plat> > getRecGeneree();
    std::vector<string> getDatesGeneree();
    std::vector<std::string> getNOMS_CATEGORIES();
    XMLParser* getParserConfig();
    std::vector<int> getNombresTemps();
    unsigned int getRepetitionCongel();
    unsigned int getRepetitionFeculent();
    unsigned int getRepetitionLegume();
    unsigned int getRepetitionViande();
    unsigned int getRepetitionAutre();

    void setNombresTemps(int id, int nomb);
    void setRepetitionCongel(int nb);
    void setRepetitionFeculent(int nb);
    void setRepetitionLegume(int nb);
    void setRepetitionViande(int nb);
    void setRepetitionAutre(int nb);
    void setEviterDoublons(bool ev);

private:
    XMLParser* pars;
    XMLParser* configuration;
    XMLParser* generee;

    std::vector<int> nombresTemps;
    unsigned int repetitionCongel;
    unsigned int repetitionFeculent;
    unsigned int repetitionLegume;
    unsigned int repetitionViande;
    unsigned int repetitionAutre;
    bool eviterDoublon;

    std::vector<std::string> NOMS_CATEGORIES;
    std::vector<std::vector<Recette*> > recettes;
    std::vector<std::vector<Recette*> > recettesRapides;
    std::vector<std::vector<Recette*> > recettesLongues;
    std::vector<std::vector<Plat> > recGeneree;
    std::vector<std::string> datesGeneree;
    Recette* recetteNULL;
    Recette* recetteVIDE;
};

#endif // DATA_H

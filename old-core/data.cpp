#include "data.h"
#include <stdlib.h>
#include "XMLParser.h"
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <QMessageBox>
#include <QCoreApplication>

using namespace std;

Data::Data(): eviterDoublon(false)
{
    /*QMessageBox msgBox;
    msgBox.setText("Chemin des fichiers.");
    msgBox.setFixedWidth(300);
    msgBox.setInformativeText("Chemins des fichiers absolue ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setIcon(QMessageBox::Question);
    int ret = msgBox.exec();

    std::string PARS_FILE;
    std::string CONFIGURATION_FILE;
    std::string GENEREE_FILE;

    if(ret == QMessageBox::Yes)
    {
        PARS_FILE = "/Users/thomasbeck/Desktop/ThomChef3/recettes3.xml";
        CONFIGURATION_FILE = "/Users/thomasbeck/Desktop/ThomChef3/config3.xml";
        GENEREE_FILE = "/Users/thomasbeck/Desktop/ThomChef3/generee3.xml";
    }
    else
    {
        PARS_FILE = QCoreApplication::applicationDirPath().toStdString() + "/" + "recettes.xml";
        CONFIGURATION_FILE = QCoreApplication::applicationDirPath().toStdString() + "/" + "config.xml";
        GENEREE_FILE = QCoreApplication::applicationDirPath().toStdString() + "/" + "generee.xml";
    }*/

    std::string PARS_FILE(QCoreApplication::applicationDirPath().toStdString() + "/" + "recettes.xml");
    std::string CONFIGURATION_FILE(QCoreApplication::applicationDirPath().toStdString() + "/" + "config.xml");
    std::string GENEREE_FILE(QCoreApplication::applicationDirPath().toStdString() + "/" + "generee.xml");

    NOMS_CATEGORIES.push_back("feculent");
    NOMS_CATEGORIES.push_back("legume");
    NOMS_CATEGORIES.push_back("viande");
    NOMS_CATEGORIES.push_back("autre");

    pars = new XMLParser(PARS_FILE);
    configuration = new XMLParser(CONFIGURATION_FILE);
    generee = new XMLParser(GENEREE_FILE);

    recetteNULL = new Recette("NULL", 0, "", vector<string>(0), false);
    recetteVIDE = new Recette("", 0, "", vector<string>(0), false);
    nombresTemps.push_back(0);
    nombresTemps.push_back(0);
    srand(time(0));
}

Data::~Data()
{
    //delete pars;
    delete configuration;
    //delete generee;
    delete recetteNULL;
    for(unsigned int i(0);i<recettes.size();++i)
    {
        for(unsigned int j(0);j<recettes[i].size();++j)
        {
            delete recettes[i][j];
        }
    }
}

void Data::init()
{
    recettes.clear();
    datesGeneree.clear();
    recGeneree.clear();

    // Chargement de toutes les recettes..
    pars->load();
    configuration->load();
    generee->load();

    // Chargement de la configuration
    bool configOK(true);

    Item* theIt;
    if(configuration->getDoc().size()>0)
    {
        theIt = configuration->getDoc()[0];
        if(configuration->getDoc()[0] == NULLItem)
        {
            configOK = false;
        }
    }
    else
    {
        theIt = NULLItem;
        configOK = false;
    }

    while(theIt != NULLItem)
    {
        if(theIt->name == "configuration" and theIt->child != NULLItem)
        {
            theIt = theIt->child;
        }
        if(theIt->name == "repetitioncongel")
        {
            repetitionCongel = stringToInt(theIt->value);
        }
        else if(theIt->name == "repetitionfeculent")
        {
            repetitionFeculent = stringToInt(theIt->value);
        }
        else if(theIt->name == "repetitionlegume")
        {
            repetitionLegume = stringToInt(theIt->value);
        }
        else if(theIt->name == "repetitionviande")
        {
            repetitionViande = stringToInt(theIt->value);
        }
        else if(theIt->name == "repetitionautre")
        {
            repetitionAutre = stringToInt(theIt->value);
        }
        theIt = theIt->next;
    }

    // Recettes
    Recette* recetteTemp;
    for(int i(0);i<NOMS_CATEGORIES.size();++i)
    {
        recettes.push_back(vector<Recette*>(0));
        recettesRapides.push_back(vector<Recette*>(0));
        recettesLongues.push_back(vector<Recette*>(0));

    }

    if(pars->getDoc().size()>0)
        theIt = pars->getDoc()[0];
    else
        theIt = NULLItem;

    while(theIt != NULLItem and configOK)
    {
        recetteTemp = new Recette(theIt);
        recettes[recetteTemp->getCategorie()].push_back(recetteTemp);
        if(recetteTemp->getTemps()==RAPIDE)
        {
            recettesRapides[recetteTemp->getCategorie()].push_back(recetteTemp);
        }
        if(recetteTemp->getTemps()==LONG)
        {
            recettesLongues[recetteTemp->getCategorie()].push_back(recetteTemp);
        }
        theIt = theIt->next;
    }


    // Chargement des recettes générées
    if(generee->getDoc().size() > 0)
    {
        Item* itG = generee->getDoc()[0];
        while(itG != NULLItem)
        {
            if(itG->name == "generation")
            {
                Item* itGC = itG->child;
                while(itGC != NULLItem)
                {
                    if(itGC->name == "date")
                    {
                        datesGeneree.push_back(itGC->value);
                    }
                    else if(itGC->name == "list")
                    {
                        Item* itG2 = itGC->child;
                        while(itG2 != NULLItem)
                        {
                            if(itG2->name == "repas")
                            {
                                Item* itG3 = itG2->child;
                                Plat pt;
                                while(itG3 != NULLItem)
                                {
                                    if(itG3->name == "item")
                                    {
                                        pt.push_back(findRecette(itG3->value));
                                    }
                                    itG3 = itG3->next;
                                }
                                if(recGeneree.size() < datesGeneree.size())
                                {
                                    recGeneree.push_back(std::vector<Plat>(0));
                                }
                                recGeneree[datesGeneree.size()-1].push_back(pt);
                            }
                            itG2 = itG2->next;
                        }
                    }
                    itGC = itGC->next;
                }
            }
            itG = itG->next;
        }
    }

}

vector<Plat> Data::randomdays(int nbrRapide, int nbrLongues)
{
    vector<Plat> rand;

    // Sauvegarde des recettes actuelles
    vector<vector<Recette*> > recettesBackup(recettes);
    vector<vector<Recette*> > recettesLonguesBackup(recettesLongues);
    vector<vector<Recette*> > recettesRapidesBackup(recettesRapides);

    // Ajout des recettes au congel, le nombre de fois que l'on veut.
    for(int i(0);i<repetitionCongel;++i)
    {
        for(unsigned int j(0);j<recettes.size();++j)
        {
            unsigned int sizeJ(recettes[j].size());
            for(unsigned int k(0);k<sizeJ;++k)
            {
                if(recettes[j][k]->getCongel())
                {
                    if(recettes[j][k]->getTemps()==RAPIDE)
                    {
                        recettes[j].push_back(recettes[j][k]);
                        recettesRapides[j].push_back(recettes[j][k]);
                    }
                    else
                    {
                        recettes[j].push_back(recettes[j][k]);
                        recettesLongues[j].push_back(recettes[j][k]);
                    }
                }
            }
        }
    }

    // Algorithm de choix aléatoire.
    // Nombre de rapides :
    unsigned int compteur(0);
    for(int j(0);j<nbrRapide and compteur<(nbrRapide+nbrLongues);++j)
    {
        unsigned int stop(100);     // Pour éviter les boucles infinis s'il ne trouve pas d'autre recette qui ne soit pas doublon.
        bool doublon(false);
        Plat pt;
        do{                         // Eviter les doublons...
            doublon = false;
            pt = random1day(recettesRapides);
            for(int a(0);a<rand.size();++a)
            {
                if(rand[a]==pt)
                {
                    doublon = true;
                }
                else if(rand[a].size()==pt.size() and eviterDoublon)        // Bloc de code pour éviter toute "ingrédient" de plat
                {                                           // En double...
                    for(int b(0);b<rand[a].size();++b)
                    {
                        if(rand[a][b]==pt[b])
                        {
                            doublon = true;
                        }
                    }
                }
            }
        }while(doublon and stop>1);
        rand.push_back(pt);
        if(pt.size()>0)
        {
            compteur += pt[0]->getNombreRepas();
        }
    }
    for(int j(0);j<nbrLongues and compteur<(nbrRapide+nbrLongues);++j)
    {
        unsigned int stop(100);
        bool doublon(false);
        Plat pt;
        do{
            doublon = false;
            pt = random1day(recettesLongues);
            for(int a(0);a<rand.size();++a)
            {
                if(rand[a]==pt)
                {
                    doublon = true;
                }
                else if(rand[a].size()==pt.size() and eviterDoublon)
                {
                    for(int b(0);b<rand[a].size();++b)
                    {
                        if(rand[a][b]==pt[b])
                        {
                            doublon = true;
                        }
                    }
                }
            }
        }while(doublon and stop>1);
        rand.push_back(pt);
        if(pt.size()>0)
        {
            compteur += pt[0]->getNombreRepas();
        }
    }

    // Retour à la normal...
    recettes = recettesBackup;
    recettesLongues = recettesLonguesBackup;
    recettesRapides = recettesRapidesBackup;

    return rand;
}

Plat Data::random1day(unsigned int temps)
{
    if(temps==RAPIDE)
    {
        return random1day(recettesRapides);
    }
    else
    {
        return random1day(recettesLongues);
    }
}

Plat Data::random1day(std::vector<std::vector<Recette*> > const& recs)
{
    Plat rand;
    // Choix de la catégories selon les "poids" de probabilités...
    int i(0);
    do{
        i = randomNum(repetitionFeculent + repetitionLegume + repetitionViande + repetitionAutre);
        if(i<repetitionFeculent)
        {
            i = FECULENT;
        }
        else if(i>=repetitionFeculent and i<repetitionLegume)
        {
            i = LEGUME;
        }
        else if(i>=repetitionLegume and i<repetitionViande)
        {
            i = VIANDE;
        }
        else
        {
            i = AUTRE;
        }
    }while(recs[i].size()<1);


    if(recs[i].size() > 0)
    {
        int num(0);
        num = randomNum(recs[i].size());
        rand.push_back(recs[i][num]);
        if(recs[i][num]->getCategorie() != AUTRE)
        {
            int autreCat(0);
            switch(recs[i][num]->getCategorie()){
            case FECULENT:
                autreCat = randomNum(repetitionViande+repetitionLegume);
                if(autreCat<repetitionViande)
                {
                    // viande
                    if(recs[VIANDE].size()>0)
                    {
                        int autre(randomNum(recs[VIANDE].size()));
                        rand.push_back(recs[VIANDE][autre]);
                    }
                }
                else
                {
                    //légume
                    if(recs[LEGUME].size()>0)
                    {
                        int autre(randomNum(recs[LEGUME].size()));
                        rand.push_back(recs[LEGUME][autre]);
                    }
                }
                break;
            case LEGUME:
                autreCat = randomNum(repetitionFeculent+repetitionViande);
                if(autreCat<repetitionFeculent)
                {
                    //féculent
                    if(recs[FECULENT].size()>0)
                    {
                        int autre(randomNum(recs[FECULENT].size()));
                        rand.push_back(recs[FECULENT][autre]);
                    }
                }
                else
                {
                    // viande
                    if(recs[VIANDE].size()>0)
                    {
                        int autre(randomNum(recs[VIANDE].size()));
                        rand.push_back(recs[VIANDE][autre]);
                    }
                }
                break;
            case VIANDE:
                autreCat = randomNum(repetitionFeculent+repetitionLegume);
                if(autreCat<repetitionFeculent)
                {
                    //féculent
                    if(recs[FECULENT].size()>0)
                    {
                        int autre(randomNum(recs[FECULENT].size()));
                        rand.push_back(recs[FECULENT][autre]);
                    }
                }
                else
                {
                    // légume
                    if(recs[LEGUME].size()>0)
                    {
                        int autre(randomNum(recs[LEGUME].size()));
                        rand.push_back(recs[LEGUME][autre]);
                    }
                }
                break;
            }
        }
    }
    return rand;
}

int Data::randomNum(int size)
{
    return rand() % size;
}


int Data::stringToInt(string s)
{
    return atoi(s.c_str());
}

std::string Data::intToString(int i)
{
    ostringstream ss;
    ss << i;
    string str(ss.str());
    return str;
}

bool Data::findDoublon(std::string n)
{
    bool doublon(false);
    for(unsigned int i(0);i<recettes.size();++i)
    {
        for(unsigned int j(0);j<recettes[i].size();++j)
        {
            if(recettes[i][j]->getNom()==n)
            {
                doublon = true;
            }
        }
    }
    return doublon;
}


Recette* Data::findRecette(std::string name)
{
    Recette* theRecipe(recetteNULL);
    bool continu(true);
    for(unsigned int i(0);i<recettes.size();++i)
    {
        for(unsigned int j(0);j<recettes[i].size() and continu;++j)
        {
            if(recettes[i][j]->getNom() == name)
            {
                theRecipe = recettes[i][j];
                continu = false;
            }
        }
    }
    return theRecipe;
}

std::vector<Recette*> Data::findRecettePartial(std::string name)
{
    std::vector<Recette*> theRecipe;
    QString Qname(name.c_str());
    Qname = Qname.toUpper();
    for(unsigned int i(0);i<recettes.size();++i)
    {
        for(unsigned int j(0);j<recettes[i].size();++j)
        {
            QString Qnom(recettes[i][j]->getNom().c_str());
            Qnom = Qnom.toUpper();
            std::string nom(Qnom.toStdString());
            if(nom.find(Qname.toStdString()) != std::string::npos)
            {
                theRecipe.push_back(recettes[i][j]);
            }
        }
    }
    return theRecipe;
}

void Data::updateFile()
{
    // Effacer puis réécrire toutes les recettes dans le fichier recettes.xml.
    std::vector<Item*> doc;
    int iDoc(0);
    for(unsigned int i(0);i<recettes.size();++i)
    {
        for(unsigned int j(0);j<recettes[i].size();++j)
        {
            doc.push_back(new Item("Plat",0));
            int parentDoc(iDoc);

            ++iDoc;
            doc.push_back(new Item("nom",1));
            doc[parentDoc]->child = doc[iDoc];
            doc[iDoc]->parent = doc[parentDoc];
            doc[iDoc]->value = recettes[i][j]->getNom().c_str();

            ++iDoc;
            doc.push_back(new Item("categorie",1));
            doc[iDoc]->parent = doc[parentDoc];
            doc[iDoc-1]->next = doc[iDoc];
            //ostringstream ss;
            //ss << recettes[i][j]->getCategorie();
            //string cat(ss.str());
            doc[iDoc]->value = intToString(recettes[i][j]->getCategorie());

            ++iDoc;
            doc.push_back(new Item("temps",1));
            doc[iDoc]->parent = doc[parentDoc];
            doc[iDoc-1]->next = doc[iDoc];
            //ostringstream ss2;
            //ss2 << recettes[i][j]->getTemps();
            //string tps(ss2.str());
            doc[iDoc]->value = intToString(recettes[i][j]->getTemps());

            ++iDoc;
            doc.push_back(new Item("ingredients",1));
            doc[iDoc]->parent = doc[parentDoc];
            doc[iDoc-1]->next = doc[iDoc];
            int beforeNext(iDoc);

            ++iDoc;
            for(unsigned int k(0);k<recettes[i][j]->getTableauIngredients().size();++k)
            {
                doc.push_back(new Item("item",2));
                if(k==0)
                {
                    doc[beforeNext]->child = doc[iDoc];
                }
                doc[iDoc]->parent = doc[beforeNext];
                if(k>0)
                {
                    doc[iDoc-1]->next = doc[iDoc];
                }
                doc[iDoc]->value = recettes[i][j]->getTableauIngredients()[k].c_str();
                ++iDoc;
            }

            doc.push_back(new Item("description",1));
            doc[iDoc]->parent = doc[parentDoc];
            doc[beforeNext]->next = doc[iDoc];
            doc[iDoc]->value = recettes[i][j]->getDescription().c_str();

            ++iDoc;
            doc.push_back(new Item("congelateur",1));
            doc[iDoc]->parent = doc[parentDoc];
            doc[iDoc-1]->next = doc[iDoc];
            if(recettes[i][j]->getCongel())
                doc[iDoc]->value = "1";
            else
                doc[iDoc]->value = "0";

            ++iDoc;
            doc.push_back(new Item("aretirer",1));
            doc[iDoc]->parent = doc[parentDoc];
            doc[iDoc-1]->next = doc[iDoc];
            if(recettes[i][j]->getARetirer())
                doc[iDoc]->value = "1";
            else
                doc[iDoc]->value = "0";

            ++iDoc;
            doc.push_back(new Item("datecongel",1));
            doc[iDoc]->parent = doc[parentDoc];
            doc[iDoc-1]->next = doc[iDoc];
            doc[iDoc]->value = recettes[i][j]->getDateCongel();

            ++iDoc;
            doc.push_back(new Item("nombrerepas",1));
            doc[iDoc]->parent = doc[parentDoc];
            doc[iDoc-1]->next = doc[iDoc];
            doc[iDoc]->value = intToString(recettes[i][j]->getNombreRepas());

            ++iDoc;
        }
    }

    pars->save(doc);
    pars->load();
    init();
    for(unsigned int i(0);i<doc.size();++i)
    {
        delete doc[i];
    }
}

void Data::updateConfig()
{
    // Effacer puis réécrire le fichier de config.
    std::vector<Item*> doc;
    doc.push_back(new Item("configuration", 0));
    int iDoc(0);

    doc.push_back(new Item("repetitioncongel",1));
    ++iDoc;
    doc[iDoc]->parent = doc[0];
    //doc[docTps]->next = doc[iDoc];
    doc[iDoc]->value = intToString(repetitionCongel);

    doc.push_back(new Item("repetitionfeculent",1));
    ++iDoc;
    doc[iDoc]->parent = doc[0];
    doc[iDoc-1]->next = doc[iDoc];
    doc[iDoc]->value = intToString(repetitionFeculent);

    doc.push_back(new Item("repetitionlegume",1));
    ++iDoc;
    doc[iDoc]->parent = doc[0];
    doc[iDoc-1]->next = doc[iDoc];
    doc[iDoc]->value = intToString(repetitionLegume);

    doc.push_back(new Item("repetitionviande",1));
    ++iDoc;
    doc[iDoc]->parent = doc[0];
    doc[iDoc-1]->next = doc[iDoc];
    doc[iDoc]->value = intToString(repetitionViande);

    doc.push_back(new Item("repetitionautre",1));
    ++iDoc;
    doc[iDoc]->parent = doc[0];
    doc[iDoc-1]->next = doc[iDoc];
    doc[iDoc]->value = intToString(repetitionAutre);

    configuration->save(doc);
    configuration->load();
    for(unsigned int i(0);i<doc.size();++i)
    {
        delete doc[i];
    }
}

void Data::updateGeneree()
{
    // Effacer puis réécrire toutes les recettes générée (recGeneree) dans le fichier generee.xml.
    std::vector<Item*> doc;
    int iDoc(0);
    for(unsigned int i(0);i<recGeneree.size();++i)
    {
        doc.push_back(new Item("generation",0));
        int parentDoc(iDoc);

        ++iDoc;
        doc.push_back(new Item("date",1));
        doc[parentDoc]->child = doc[iDoc];
        doc[iDoc]->parent = doc[parentDoc];
        doc[iDoc]->value = datesGeneree[i];

        ++iDoc;
        doc.push_back(new Item("list",1));
        doc[iDoc]->parent = doc[parentDoc];
        doc[iDoc-1]->next = doc[iDoc];
        int beforeNext(iDoc);

        ++iDoc;
        int docFor(iDoc);
        for(unsigned int j(0);j<recGeneree[i].size();++j)
        {
            doc.push_back(new Item("repas",2));
            if(j==0)
            {
                doc[beforeNext]->child = doc[iDoc];
            }
            doc[iDoc]->parent = doc[beforeNext];
            if(j>0)
            {
                doc[docFor]->next = doc[iDoc];
                docFor = iDoc;
            }

            int beforebeforeNext(iDoc);
            ++iDoc;
            for(unsigned int k(0);k<recGeneree[i][j].size();++k)
            {
                doc.push_back(new Item("item",3));
                if(k==0)
                {
                    doc[beforebeforeNext]->child = doc[iDoc];
                }
                doc[iDoc]->parent = doc[beforebeforeNext];
                if(k>0)
                {
                    doc[iDoc-1]->next = doc[iDoc];
                }
                doc[iDoc]->value = recGeneree[i][j][k]->getNom();

                ++iDoc;
            }
        }
    }

    generee->save(doc);
    generee->load();
    for(unsigned int i(0);i<doc.size();++i)
    {
        delete doc[i];
    }
}


std::vector<std::vector<Recette*> > Data::getRecettes()
{
    return recettes;
}

std::vector<std::vector<Plat> > Data::getRecGeneree()
{
    return recGeneree;
}

std::vector<std::string> Data::getDatesGeneree()
{
    return datesGeneree;
}

XMLParser* Data::getParserConfig()
{
    return configuration;
}

std::vector<std::string> Data::getNOMS_CATEGORIES()
{
    return NOMS_CATEGORIES;
}

std::vector<int> Data::getNombresTemps()
{
    return nombresTemps;
}

unsigned int Data::getRepetitionCongel()
{
    return repetitionCongel;
}

unsigned int Data::getRepetitionFeculent()
{
    return repetitionFeculent;
}

unsigned int Data::getRepetitionLegume()
{
    return repetitionLegume;
}

unsigned int Data::getRepetitionViande()
{
    return repetitionViande;
}

unsigned int Data::getRepetitionAutre()
{
    return repetitionAutre;
}

void Data::setRepetitionCongel(int nb)
{
    repetitionCongel = nb;
    updateConfig();
}

void Data::setRepetitionFeculent(int nb)
{
    repetitionFeculent = nb;
    updateConfig();
}

void Data::setRepetitionLegume(int nb)
{
    repetitionLegume = nb;
    updateConfig();
}

void Data::setRepetitionViande(int nb)
{
    repetitionViande = nb;
    updateConfig();
}

void Data::setRepetitionAutre(int nb)
{
    repetitionAutre = nb;
    updateConfig();
}

void Data::setNombresTemps(int id, int nomb)
{
    nombresTemps[id] = nomb;
    updateConfig();
}

void Data::ajouterARetirer(Recette* rec)
{
    rec->setARetirer(true);
    updateFile();
}

void Data::supprimerGeneration(int indice)
{
    std::vector<std::string> datesNew;
    std::vector<std::vector<Plat> > recNew;
    for(unsigned int i(0);i<datesGeneree.size();++i)
    {
        if(i!=indice)
        {
            datesNew.push_back(datesGeneree[i]);
            recNew.push_back(recGeneree[i]);
        }
    }
    datesGeneree = datesNew;
    recGeneree = recNew;
    updateGeneree();
}

void Data::supprimerGeneration(std::vector<int> indice)
{
    std::vector<std::string> datesNew;
    std::vector<std::vector<Plat> > recNew;
    for(unsigned int i(0);i<datesGeneree.size();++i)
    {
        bool ajout(true);
        for(unsigned int j(0);j<indice.size();++j)
        {
            if(i==indice[j])
            {
                ajout = false;
            }
        }
        if(ajout)
        {
            datesNew.push_back(datesGeneree[i]);
            recNew.push_back(recGeneree[i]);
        }
    }
    datesGeneree = datesNew;
    recGeneree = recNew;
    updateGeneree();
}

void Data::supprimerRecGeneration(QStringList noms, int date)
{
    std::vector<Plat> newRec;
    bool bonneRec(true);
    bool continuer(true);
    for(unsigned int i(0);i<recGeneree[date].size();++i)
    {
        int recGenSize(recGeneree[date][i].size());
        if(recGenSize != noms.size())
        {
            bonneRec = false;
        }
        for(unsigned int j(0);j<min(recGenSize, noms.size());++j)
        {
            if(recGeneree[date][i][j]->getNom() != noms[j].toStdString())
            {
                bonneRec = false;
            }
        }
        if(!bonneRec or continuer==false)
        {
            newRec.push_back(recGeneree[date][i]);
        }
        else
        {
            continuer = false;
        }
        bonneRec = true;
    }
    recGeneree[date] = newRec;

    updateGeneree();
}

void Data::addRecette(Recette* rec)
{
    recettes[rec->getCategorie()].push_back(rec);
    updateFile();
}

void Data::modifierRecette(Recette* rec, std::string formerNom)
{
    Recette* amodifier = findRecette(formerNom);
    amodifier->setNom(rec->getNom());
    amodifier->setCategorie(rec->getCategorie());
    amodifier->setTemps(rec->getTemps());
    amodifier->setDescription(rec->getDescription());
    amodifier->setTableauIngredients(rec->getTableauIngredients());
    amodifier->setCongel(rec->getCongel());
    amodifier->setARetirer(rec->getARetirer());
    amodifier->setDateCongel(rec->getDateCongel());
    amodifier->setNombreRepas(rec->getNombreRepas());
    updateFile();
}

void Data::modifierGeneration(int numDate, string nom, Plat newPlat)
{
    for(unsigned int i(0);i<recGeneree[numDate].size();++i)
    {
        if(recGeneree[numDate][i].size()>0)
        {
            if(recGeneree[numDate][i][0]->getNom() == nom)
            {
                recGeneree[numDate][i] = newPlat;
            }
        }
    }
    updateGeneree();
}

void Data::ajouterGeneration(std::string date, std::vector<Plat> plats)
{
    datesGeneree.push_back(date);
    recGeneree.push_back(plats);
    updateGeneree();
}

void Data::ajouterRecGeneration(int date, Plat pt)
{
    recGeneree[date].push_back(pt);
    updateGeneree();
}

void Data::supprimerRecette(std::string nomRec)
{
    std::vector<std::vector<Recette*> > newRecettes;
    for(unsigned int i(0);i<recettes.size();++i)
    {
        newRecettes.push_back(std::vector<Recette*>(0));
        for(unsigned int j(0);j<recettes[i].size();++j)
        {
            if(recettes[i][j]->getNom() != nomRec)
            {
                newRecettes[i].push_back(recettes[i][j]);
            }
        }
    }
    recettes = newRecettes;
    updateFile();
}

void Data::setEviterDoublons(bool ev)
{
    eviterDoublon = ev;
}

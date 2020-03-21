#include "recette.h"
#include <sstream>

Recette::Recette()
{
}

Recette::Recette(std::string nomR, int catR, std::string descR, vector<std::string> ingredientsR, bool congelR)
{
    nom = nomR;
    categorie = catR;
    temps = RAPIDE;
    description = descR;
    ingredients = ingredientsR;
    congel = congelR;
    aRetirer = false;
    dateCongel = "0";
    nbRepas = 1;
}

Recette::Recette(Item* it)
{

    it = it->child;
    while(it != NULLItem)
    {
        if(it->name == "nom")
        {
            nom = it->value;
        }
        else if(it->name == "categorie")
        {
            char maDeuxiemeString(it->value[0]);
            stringstream ss;
            ss << maDeuxiemeString;
            int valueInt(0);
            ss >> valueInt;
            categorie = valueInt;
        }
        else if(it->name == "temps")
        {
            char maDeuxiemeString(it->value[0]);
            stringstream ss;
            ss << maDeuxiemeString;
            int valueInt(0);
            ss >> valueInt;
            temps = valueInt;
        }
        else if(it->name == "description")
        {
            description = it->value;
        }
        else if(it->name == "congelateur")
        {
            congel = stringToBool(it->value);
        }
        else if(it->name == "aretirer")
        {
            aRetirer = stringToBool(it->value);
        }
        else if(it->name == "datecongel")
        {
            dateCongel = it->value;
        }
        else if(it->name == "ingredients")
        {
            Item* itI = it->child;
            while(itI != NULLItem)
            {
                ingredients.push_back(itI->value);
                itI = itI->next;
            }
        }
        else if(it->name == "nombrerepas")
        {
            nbRepas = stringToInt(it->value);
        }
        else
        {
            // ERROR
            cerr << "Erreur de lecture du fichier base de données." << endl;
        }

        it = it->next;
    }
}


string Recette::getNom()
{
    return nom;
}

int Recette::getCategorie()
{
    return categorie;
}

int Recette::getTemps()
{
    return temps;
}

bool Recette::getARetirer()
{
    return aRetirer;
}

string Recette::getDescription()
{
    return description;
}

string Recette::getIngredients()
{
    string txt("");
    for(int i(0);i<ingredients.size();++i)
    {
        txt += " - " + ingredients[i] + " \n";
    }
    return txt;
}

std::vector<std::string> Recette::getTableauIngredients()
{
    return ingredients;
}

bool Recette::getCongel()
{
    return congel;
}

string Recette::getDateCongel()
{
    return dateCongel;
}


unsigned int Recette::getNombreRepas()
{
    return nbRepas;
}

void Recette::setNom(string n)
{
    nom = n;
}

void Recette::setCategorie(int c)
{
    categorie = c;
}

void Recette::setTemps(int t)
{
    temps = t;
}

void Recette::setDescription(string desc)
{
    description = desc;
}

void Recette::setTableauIngredients(vector<string> ing)
{
    ingredients = ing;
}

void Recette::setCongel(bool value)
{
    congel = value;
}

void Recette::setARetirer(bool value)
{
    aRetirer = value;
}

void Recette::setDateCongel(string date)
{
    dateCongel = date;
}


void Recette::setNombreRepas(unsigned int nb)
{
    nbRepas = nb;
}

bool Recette::stringToBool(string laString)
{
    return laString != "0";
}

int Recette::stringToInt(string laString)
{
    int thevalue(0);
    //laString = "43";
    std::istringstream(laString) >> thevalue;
    return thevalue;
}

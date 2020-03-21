#include "XMLParser.h"

Item* const NULLItem = new Item("NULL", 0);

/*
 * Function declarations of the class Item
 *
 */

Item::Item(string itemName,int itemLevel) : name(itemName), level(itemLevel), value("")
{
    if (name.compare("NULL")!=0) {
        //initialise();
        next = NULLItem;
        parent = NULLItem;
        child = NULLItem;
    }
    else {
        next = this;
        parent = this;
        child = this;
    }

}
Item::~Item()
{
}

/*void Item::initialise()
{
    next = NULLItem;
    parent = NULLItem;
    child = NULLItem;
}*/

// Tests if it's the NULLItem
bool Item::isNull() const
{
    bool isN(false);
    if (this == NULLItem) {
        isN = true;
    }
    return isN;
}

// Overloading of operator[] for Item if there's a series of [][] (the first
// is returning an Item, then the second is applied on the class Item)
Item* Item::operator[](int index)
{
    Item* theItem = this;
    if (theItem->child != NULLItem) {
        theItem = theItem->child;
        int i(0);
        while (theItem->next != NULLItem and i<index) {
            theItem = theItem->next;
            ++i;
        }
        if (theItem->next == NULLItem and i<index) {
            theItem = NULLItem;				// CONVENTION : the Item named "NULL" is the NULL-item (avoiding segmentation faults)
        }
    }
    else {
        theItem = NULLItem;
    }
    return theItem;
}















/*
 * Function declarations of the class XMLParser
 *
 */



XMLParser::XMLParser(string parserFile) : file(parserFile)
{}

XMLParser::~XMLParser()
{
    for (int i(0); i<doc.size(); ++i) {
        if (doc[i] != NULLItem)
            delete doc[i];
    }
    delete NULLItem;
}

vector<Item*> XMLParser::getDoc() const
{
    return doc;
}

unsigned int XMLParser::rootSize() const
{
    int size(0);
    if (doc.size() != 0) {
        size = 1;
        Item* it = doc[0];
        while (it->next != NULLItem) {
            it = it->next;
            ++size;
        }
    }
    return size;
}


void XMLParser::load()
{
    doc.clear();
    balises.clear();
    values.clear();
    // Extract tags from the file :
    extractTags();

    try {
        vector<Item*> openedTags; // Opened tags which are not closed straight after.

        int current_level(0);
        Item* newItem = NULLItem;
        // The Algorithm
        for (int i(0); i<balises.size(); ++i) {
            bool closing(false);
            if (openedTags.size() > 0)
            {
                if (balises[i].compare("/" + openedTags.back()->name) == 0) {
                    --current_level;
                    testParentChild(openedTags.back());
                    openedTags.pop_back();
                    closing = true;
                }
            }
            if (closing == false) {
                newItem = new Item(balises[i],current_level);
                if (i<balises.size()-1) {
                    // Avoid wrong-typed tags like <FirstTag <SecondTag>
                    if (containsForbiddenChar(balises[i])) {
                        throw int(-1);
                    }
                    if (balises[i+1].compare("/" + balises[i]) == 0) {
                        newItem->value = values[i];
                        doc.push_back(newItem);
                        testParentChild(newItem);
                        ++i;
                    }
                    else {
                        // Avoid wrong closing tags like <item1><item2></item1></item2>
                        if ((balises[i])[0] == '/') {
                            throw int(i);
                        }
                        doc.push_back(newItem);
                        openedTags.push_back(newItem);
                        ++current_level;
                    }
                }
            }
        }
        if (doc.size()==0) {
            doc.push_back(NULLItem);				// Avoid getting an empty doc vector.
        }
    }
    catch (int index) {
        if (index==-1) {
            cerr << endl << endl << "PARSING ERROR : there's an unclosed tag" << endl << endl;
        }
        else {
            cerr << endl << endl << "PARSING ERROR (tag number " << index << ") : tag sequence is not correct for the tag : " << balises[index] << endl << endl;
        }
    }

}

void XMLParser::save(vector<Item*> data)
{
    string text("");
    for (int i(0); i<data.size(); ++i) {
        text += espaces(data[i]->level) + "<" + data[i]->name + ">";
        if (data[i]->value.compare("") != 0) {
            text += data[i]->value;
        }
        if (data[i]->child == NULLItem) {				// If the data has no child, then we close the tags needed to be closed.
            text += "</" + data[i]->name + "> \n";
            Item* aFermerNext = data[i]->next;
            Item* aFermer = data[i];
            // While there's a parent and no next tags, we close the tags needed to be closed...
            while (aFermerNext == NULLItem and aFermer->parent != NULLItem) {
                text += espaces(aFermer->parent->level) + "</" + aFermer->parent->name + "> \n";
                aFermerNext = aFermer->parent->next;
                aFermer = aFermer->parent;
            }
        }
        else {
            text += "\n";
        }

    }

    ofstream sortie;
    try {
        sortie.open(file.c_str(), std::ofstream::out | std::ofstream::trunc);
        sortie << text;
        sortie.close();
    }
    catch (int e) {
        cerr << "ERREUR " << e << " : Impossible d'ouvrir le fichier " << file <<" (en sortie)." << endl;
    }

    load();
}

// Overloading of operator[] to access Items like XMLParser[1][2] 2nd item of 0 level, 3rd item of level 1.
Item* XMLParser::operator[](int index)
{
    Item* theItem = doc[0];
    int i(0);
    while (theItem->next != NULLItem and i<index) {
        theItem = theItem->next;
        ++i;
    }
    if (theItem->next == NULLItem and i<index and i != 0) {
        theItem = NULLItem;						// CONVENTION : to avoid segmentation faults.
    }
    return theItem;
}

// Make the right indentation for tags during the writting of the file.
string XMLParser::espaces(int nbEspace)
{
    string esp("");
    for (int i(0); i<nbEspace; ++i) {
        esp += "    ";
    }
    return esp;
}

void XMLParser::makeLevel(vector<Item*> lev, Item* parentItem)
{
    for (int i(0); i<lev.size(); ++i) {
        lev[i]->parent = parentItem;
        if (i<(lev.size()-1))
            lev[i]->next = lev[i+1];
    }
    if (parentItem != NULLItem)
        parentItem->child = lev[0];
}

// test if there exists a tag which is parent of [Item*] it
// and also if the previous tag needs to take [Item*] it as next.
void XMLParser::testParentChild(Item* it)
{
    int index(0);
    // Find the nearer tag, at the same level.
    for (int i(0); i<doc.size(); ++i) {
        if (doc[i]->name.compare(it->name) == 0)
            index = i;
    }
    bool doElse(true); // For the else condition.
    if (doc.size()>1 and index>=1) {
        if (doc[index-1]->level == doc[index]->level) { // previous tag has same level
            doc[index-1]->next = doc[index];
            doc[index]->parent = doc[index-1]->parent;
            doElse = false;
        }
        else if (doc[index-1]->level == (doc[index]->level - 1)) { // previous tag is a parent
            doc[index-1]->child = doc[index];
            doc[index]->parent = doc[index-1];
            doElse = false;
        }
        else {
            doElse = true;
        }
    }
    if (doElse) {											// Previous tag is not straight before.
        Item* thePrevious = NULLItem;
        for (int a(0); a<doc.size(); ++a) {
            if (doc[a]->level == doc[index]->level and a != index) { // Find the nearer tag which has same level
                thePrevious = doc[a];				// that is, the previous tag on same level.
            }
        }
        if (thePrevious != NULLItem) {
            thePrevious->next = doc[index];
        }
    }

}

// Removes the spaces at the beginning and end of the [string] text.
string XMLParser::removeSpaces(string const& txt)
{
    string newText(txt);
    while (newText[0]==' ') {
        newText = newText.substr(1,newText.size()-1);
    }
    while (newText[newText.size()-1] == ' ') {
        newText = newText.substr(0,newText.size()-1);
    }
    return newText;
}

// Check if there exist a forbidden caracter like '<' or '>'.
bool XMLParser::containsForbiddenChar(string const& txt)
{
    bool thereis(false);
    for (int i(0); i<txt.size(); ++i) {
        if (txt[i] == '<' or txt[i] == '>') {
            thereis = true;
        }
    }
    return thereis;
}

void XMLParser::extractTags()
{
    // Open the file...
    ifstream entree(file.c_str());
    //entree.open(file.c_str());
    if (entree.fail())
        cerr << "ERREUR : ouverture du fichier XML " << file << " impossible!" << endl;
    else
    {
        try
        {
            // Loop over all the lines of the text file.
            string ligne("");
            string text("");
            while (getline(entree,ligne)) {
                text = text + " \n" + ligne;
            }

            // Algorithm which takes the tags and text apart in the vectors balises and values...
            int compteur(0);
            while(text.find("<", compteur) != string::npos)
            {
                // If it's not a comment
                if (text[text.find("<", compteur) + 1] != '!') {
                    int debBalise(text.find("<", compteur) + 1);
                    int finBalise(text.find(">", debBalise));
                    balises.push_back(text.substr(debBalise,(finBalise-debBalise)));
                    compteur = finBalise;
                    int debValue(compteur+1);
                    int finValue(text.find("<", compteur));
                    values.push_back(removeSpaces(text.substr(debValue,(finValue-debValue))));
                }
                else {
                    compteur = text.find(">", compteur)+1;
                }
            }

        }
        catch (int erreur) {
            cerr << "ERREUR " << erreur << " : Le fichier XML " << file << " ne peut pas s'ouvrir." << endl;
        }
    }

    // Close the file...
    entree.close();
}

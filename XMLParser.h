/*
 *  includeXMLParser.h
 *  
 *
 *  Created by Thomas BECK on 22/06/13.
 *  Copyright 2013 EPFL. All rights reserved.
 *
 *	NULLItem is the equivalent of NULL (pointer) for an Item*.
 *  
 *  DESCRIPTION :
 *    This two classes are aimed at parsing and writing (saving) XML-like data.
 *    This works by creating a vector-table of Item elements (first class)
 *    Each Item has a parent Item (which can point towards NULL), a child and a next Item.
 *    The next-attribute represents the next Item which is on the same level of the tree
 *    
 *  ACCESS A PARSED DOCUMENT :
 *    To access to a document, the following synthaxe has to be used :
 *      XMLParser myPars("file.xml");
 *      *myPars[1] is the root item's next element. This is equal to (myPars.getDoc())[0]->next
 *      *(*myPars[1])[2] is the third next item of the child of the root item's next element.
 *                      which is (myPars.getDoc())[0]->child->next->next
 *    Caution : when using these operators (operator[]), please make sure the returned value
 *              is not the Item NULL (Item named "NULL", of level 0, all pointers are NULL inside)
 *              In this case, the item targeted is non-existant.
 *
 *  MAKE AND SAVE A DOCUMENT :
 *    To make a document, the tree-like structure has to be made.
 *    All the Items has to be put in the right order (one after the following,
 *    like when reading tags by tags the XML document) in a vector table.
 *    To help make the levels of the tree-like structure, the XMLParser's function
 *    called makeLevel(vector<Item*> lev, Item* parent = NULLItem) can be used.
 *      This function created all the linkages between the parent and child items,
 *      including next's items.
 *    
 */

/*
 * Class Item
 *
 */

#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


class Item
{
public:
	
	Item(string itemName,int itemLevel);
	~Item();
	
	//void initialise();
	bool isNull() const;
	
	Item* operator[](int index);
	
	// Public attribute for a better access.
	string name;
    string value;
	Item* next;
	Item* parent;
	Item* child;
	int level;
};


// NULLItem is the NULL pointer-like Item (convention)
// This is done to avoid segmentation faults.
extern Item* const NULLItem;


/*
 * Class XMLParser
 *
 */

class XMLParser
{
public:
	XMLParser(string parserFile);
	~XMLParser();
	
	void load();
	void save(vector<Item*> data);
	void makeLevel(vector<Item*> lev, Item* parentItem = NULLItem);
	
	Item* operator[](int index); // Access to the first level (0-level) of the tree-like structure
	unsigned int rootSize() const;
	vector<Item*> getDoc() const;
	
private:
	void testParentChild(Item* it);
	void extractTags();
	string espaces(int nbEspace);
	string removeSpaces(string const& txt);
	bool containsForbiddenChar(string const& txt);

	vector<Item*> doc;
	// Vectors given by the function extractBalises([string] text);
	vector<string> balises;
    vector<string> values;
	// File which is parsed.
	string file;


};

#endif // XMLPARSER_H


#ifndef PROJETO__PARSER_H__
#define PROJETO__PARSER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

void exploreElement(XMLElement*);
vector<Shape*> exploreModels(XMLElement* );
void readFile(string, vector<Point*>*, vector<Point*>*, vector<Point*>*);
Group* parseXML(char*);


#endif

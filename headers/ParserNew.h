#ifndef PROJETO__PARSERNEW_H__
#define PROJETO__PARSERNEW_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "tinyxml2.h"
#include "Transform.h"
#include "Struct.h"

using namespace std;
using namespace tinyxml2;

vector<Struct> lookAux(XMLElement*);
vector<Struct> lookupFiles(char*);
int parseXML(char*);

#endif
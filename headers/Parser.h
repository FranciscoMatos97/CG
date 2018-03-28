#ifndef PROJETO__PARSER_H__
#define PROJETO__PARSER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <stdlib.h>

#include "tinyxml2.h"
#include "Transform.h"
#include "Struct.h"

using namespace std;
using namespace tinyxml2;

vector<Struct> lookAux(XMLElement*);
vector<Struct> lookFiles(char*);
vector<Point*> readFile(string);
int parseXML(char*);

#endif

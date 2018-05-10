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
#include "Light.h"
#include "Material.h"

using namespace std;
using namespace tinyxml2;

Struct readFile(string, Struct);
Struct lookUpTranslate(XMLElement*, Struct);
Struct lookUpTransformation(XMLElement*, Struct);
Struct lookUpLight(XMLElement*, Struct);
Struct lookUpMaterial(XMLElement*, Struct);
Struct lookUpModel(XMLElement*, Struct);
vector<Struct> lookAux(XMLElement*);
vector<Struct> lookFiles(char*);
int parseXML(char*);

#endif

#ifndef PROJETO__PARSER_H__
#define PROJETO__PARSER_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>

#include "tinyxml2.h"
#include "Transform.h"
#include "Struct.h"
#include "Light.h"
#include "Material.h"
#include "Scene.h"

using namespace std;
using namespace tinyxml2;

Struct readFile(string, Struct);
Struct lookUpTranslate(XMLElement*, Struct);
Struct lookUpTransformation(XMLElement*, Struct);
void lookUpLight(XMLElement*);
Struct lookUpMaterial(bool, XMLElement*, Struct);
Struct lookUpModel(XMLElement*, Struct);
vector<Struct> lookAux(XMLElement*);
Scene lookFiles(char*);
int parseXML(char*);

#endif

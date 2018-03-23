#ifndef PROJETO__PARSERNEW_H__
#define PROJETO__PARSERNEW_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "tinyxml2.h"
#include "Point.h"
#include "Transform.h"
#include "Struct.h"

using namespace std;
using namespace tinyxml2;

vector<Struct*> lookupFiles(char* file_name);
vector<Point*> readFile(string file_name);
int parseXML(char* file_name);

#endif
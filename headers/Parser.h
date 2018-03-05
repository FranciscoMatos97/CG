#ifndef PROJETO__PARSER_H__
#define PROJETO__PARSER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "tinyxml2.h"
#include "Point.h"

using namespace std;
using namespace tinyxml2;

vector<string> lookupFiles(char* file_name);
vector<Point*> readFile(string file_name);
int parseXML(char* file_name);

#endif

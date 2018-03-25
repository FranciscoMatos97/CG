#ifndef AA_PROJETO_ENGINE_H
#define AA_PROJETO_ENGINE_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;
#include "ParserNew.h"
#include "Point.h"
#include "Struct.h"

#endif //AA_PROJETO_ENGINE_H

void changeSize(int w, int h);
void figuraPrimitiva(Struct);
void sistemaSolar(Struct);
void renderScene(void);
void processKeys(unsigned char key, int xx, int yy);
void processSpecialKeys(int key, int xx, int yy);


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

using namespace std;
#include "Parser.h"
#include "Point.h"

#endif //AA_PROJETO_ENGINE_H

void changeSize(int w, int h);
void renderScene(void);
void processKeys(unsigned char key, int xx, int yy);
void processSpecialKeys(int key, int xx, int yy);

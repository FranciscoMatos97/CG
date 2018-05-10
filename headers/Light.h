#ifndef PROJETO_LIGHT_H__
#define PROJETO_LIGHT_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "Point.h"

class Light{

    int isPoint;
    Point* point;

	public:
		Light::Light();
		Light::Light(int, Point*);
		int Light::getIsPoint();
		Point* Light::getPoint();
        void Light::draw();
};

#endif

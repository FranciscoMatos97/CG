#ifndef PROJETO_MATERIAL_H__
#define PROJETO_MATERIAL_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "Point.h"
#include <time.h>

class Material{

    float diffuse[4], ambient[4], diffuseANDambient[4], specular[4], emission[4], shininess;
	bool notDiffuse, notAmbient, notDiffuseANDambient, notEmission, notSpecular;

	public:
		Material();
		Material(Point*, Point*, Point*, Point*, Point*, float, bool);
		float* getDiffuse();
		float* getAmbient();
		float* getDiffuseANDambient();
		float* getSpecular();
		float* getEmission();
		float getShininess();
		void draw();
};

#endif

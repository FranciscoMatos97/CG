#ifndef PROJETO_MATERIAL_H__
#define PROJETO_MATERIAL_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "Point.h"

class Material{

    float diffuse[4], ambient[4], diffuseANDambient[4], specular[4], emission[4], shininess;

	public:
		Material::Material();
		Material::Material(Point*, Point*, Point*, Point*, Point*, float);
		float* Material::getDiffuse();
		float* Material::getAmbient();
		float* Material::getDiffuseANDambient();
		float* Material::getSpecular();
		float* Material::getEmission();
		float Material::getShininess();
		void Material::draw();
};

#endif

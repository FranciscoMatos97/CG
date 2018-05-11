#include "../../headers/Material.h"

float diffuse[4], ambient[4], diffuseANDambient[4], specular[4], emission[4], shininess;

Material::Material(){}

Material::Material(Point* d, Point* a, Point* dAa, Point* s, Point* e, float shi){
    diffuse[0] = d->getX();
    diffuse[1] = d->getY();
    diffuse[2] = d->getZ();
    diffuse[3] = 1;

    ambient[0] = a->getX();
    ambient[1] = a->getY();
    ambient[2] = a->getZ();
    ambient[3] = 1;

    diffuseANDambient[0] = dAa->getX();
    diffuseANDambient[1] = dAa->getY();
    diffuseANDambient[2] = dAa->getZ();
    diffuseANDambient[3] = 1;

    specular[0] = s->getX();
    specular[1] = s->getY();
    specular[2] = s->getZ();
    specular[3] = 1;

    emission[0] = e->getX();
    emission[1] = e->getY();
    emission[2] = e->getZ();
    emission[3] = 1;

    shininess = shi;
}

float* Material::getDiffuse(){
    return diffuse;
}

float* Material::getAmbient(){
    return ambient;
}

float* Material::getDiffuseANDambient(){
    return diffuseANDambient;
}

float* Material::getSpecular(){
    return specular;
}

float* Material::getEmission(){
    return emission;
}

float Material::getShininess(){
    return shininess;
}

void Material::draw() {
    float a, b, c;

    if(diffuse[0]==0 && diffuse[1]==0 && diffuse[2]==0
       && ambient[0]==0 && ambient[1]==0 && ambient[2]==0
       && diffuseANDambient[0]==0 && diffuseANDambient[1]==0 && diffuseANDambient[2]==0){

        srand(1024);

        a = (float) rand() / (float) RAND_MAX;
        b = (float) rand() / (float) RAND_MAX;
        c = (float) rand() / (float) RAND_MAX;

        if (a <= 0.1 && b <= 0.1 && c <= 0.1) a = 1;

        diffuseANDambient[0]=a;
        diffuseANDambient[1]=b;
        diffuseANDambient[2]=c;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseANDambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}
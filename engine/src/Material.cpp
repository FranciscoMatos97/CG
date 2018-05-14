#include "../../headers/Material.h"

float diffuse[4], ambient[4], diffuseANDambient[4], specular[4], emission[4], shininess;
bool notDiffuse, notAmbient, notDiffuseANDambient, notEmission, notSpecular;

Material::Material(){}

Material::Material(Point* d, Point* a, Point* dAa, Point* s, Point* e, float shi, bool texture){
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

    float red, green, blue;
    notDiffuse = diffuse[0]==0 && diffuse[1]==0 && diffuse[2]==0;
    notAmbient = ambient[0]==0 && ambient[1]==0 && ambient[2]==0;
    notDiffuseANDambient = diffuseANDambient[0]==0 && diffuseANDambient[1]==0 && diffuseANDambient[2]==0;
    notEmission = emission[0]==0 && emission[1]==0 && emission[2]==0;
    notSpecular = specular[0]==0 && specular[1]==0 && specular[2]==0;

    if(notDiffuse && notAmbient && notDiffuseANDambient && notEmission && notSpecular && !texture){
        srand(time(NULL));

        red = (float) rand() / (float) RAND_MAX;
        green = (float) rand() / (float) RAND_MAX;
        blue = (float) rand() / (float) RAND_MAX;

        if (red <= 0.1 && green <= 0.1 && blue <= 0.1) red = 1;

        diffuseANDambient[0]=red;
        diffuseANDambient[1]=green;
        diffuseANDambient[2]=blue;
    }
    if(texture) {
        diffuseANDambient[0]=1;
        diffuseANDambient[1]=1;
        diffuseANDambient[2]=1;
    }
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
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

    if(diffuseANDambient[0]!=0 || diffuseANDambient[1]!=0 || diffuseANDambient[2]!=0)
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseANDambient);

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}
#include "../../headers/Material.h"

Float diffuse[4], ambient[4], diffuseANDambient[4], specular[4], emission[4], shininess;

Material::Material(Float* d, Float* a, Float* dAa, Float* s, Float* e, float shi){
    diffuse = d;
    ambient = a;
    diffuseANDambient = dAa;
    specular = s;
    emission = e;
    shininess = shi;
}

void Material::draw() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseANDambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}
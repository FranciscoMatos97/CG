#include "../../headers/Light.h"

int isPoint;
Point* point;

Light::Light(){}

Light::Light(int ip, Point* p){
    isPoint=ip;
    p=p;
}

int Light::getIsPoint(){
    return isPoint;
}

Point* Light::getPoint(){
    return point;
}

void Light::draw() {

    GLfloat pos[4] = {point->getX(), point->getY() , point->getZ(), isPoint};

    // light position
    glLightfv(GL_LIGHT0, GL_POINT, pos);

    GLfloat amb[4] = {0.1, 0.1, 0.1, 1.0};
    GLfloat diff[4] = {1.0, 1.0, 1.0, 1.0};

    // light colors
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
}
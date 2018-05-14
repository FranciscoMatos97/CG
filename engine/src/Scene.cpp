#include "../../headers/Scene.h"

vector<Light> luzes;
vector<Struct> estruturas;

Scene::Scene(){}

vector<Light> Scene::getLuzes(){
    return luzes;
}

vector<Struct> Scene::getEstruturas(){
    return estruturas;
}

void Scene::setLuzes(vector<Light> l){
    luzes = l;
}

void Scene::setEstruturas(vector<Struct> s){
    estruturas = s;
}

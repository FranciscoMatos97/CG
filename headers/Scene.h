#ifndef PROJETO_SCENE_H__
#define PROJETO_SCENE_H__

#include <vector>
#include "Light.h"
#include "Struct.h"

class Scene{

    vector<Light> luzes;
    vector<Struct> estruturas;

public:
    Scene();
	vector<Light> getLuzes();
    vector<Struct> getEstruturas();
    void setLuzes(vector<Light>);
    void setEstruturas(vector<Struct>);
};
#endif

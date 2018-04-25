#include "../../headers/Patch.h"

vector<Point*> controlPoints;

Patch::Patch(){
    
}

Patch::Patch(vector<Point*> v1){
    controlPoints = v1;
}

vector<Point*> Patch::getControlPoints(){
    return controlPoints;
}

void Patch::setCtrlPoints(vector<Point*> v1){
    controlPoints = v1;
}
#include "../../headers/Patch.h"

vector<Point*> controlPoints;
vector<Point*> ptList;

Patch::Patch(){
    
}

Patch::Patch(vector<Point*> v1, vector<Point*> v2){
    controlPoints = v1;
    ptList = v2;
}

vector<Point*> Patch::getControlPoints(){
    return controlPoints;
}

vector<Point*> Patch::getPointsList(){
    return ptList;
}

void Patch::setCtrlPoints(vector<Point*> v1){
    controlPoints = v1;
}

void Patch::setPTList(vector<Point*> v2){
    ptList = v2;
}
#ifndef PROJETO_PATCH_H__
#define PROJETO_PATCH_H__

#include <vector>
#include "Point.h"

using namespace std;

class Patch{

    vector<Point*> controlPoints;
    vector<Point*> ptList;

    public:
        Patch();
        Patch(vector<Point*>, vector<Point*>);
        vector<Point*> getControlPoints();
        vector<Point*> getPointsList();
        void setCtrlPoints(vector<Point*>);
        void setPTList(vector<Point*>);
};

#endif
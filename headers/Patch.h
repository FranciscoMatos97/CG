#ifndef PROJETO_PATCH_H__
#define PROJETO_PATCH_H__

#include <vector>
#include "Point.h"

using namespace std;

class Patch{

    vector<Point*> controlPoints;

    public:
        Patch();
        Patch(vector<Point*>);
        vector<Point*> getControlPoints();
        void setCtrlPoints(vector<Point*>);
};

#endif
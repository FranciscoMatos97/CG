#ifndef PROJETO_VERTEX_H__
#define PROJETO_VERTEX_H__

#include <math.h>
#include <iostream>
#include <vector>
#include "Point.h"
#include "Patch.h"

using namespace std;

class Vertex{

	vector<Point*> pointsList;
    vector<Point*> normalsList;
    vector<Point*> texturesList;

	public:
		Vertex();
		Vertex(vector<Point*>,vector<Point*>,vector<Point*>);
		vector<Point*> getPointsList();
		vector<Point*> getNormalsList();
        vector<Point*> getTexturesList();
        void setPointsList(vector<Point*>);
        void setNormalsList(vector<Point*>);
        void setTexturesList(vector<Point*>);
		void makePlane(float);
		void makeBox(float, float, float, int);
		void makeCone(float, float, int, int);
		void makeSphere(float, int, int);
		void makeTorus(float, float, int, int);
        Point* bezierCurve(float, Point*, Point*, Point*, Point*);
        Point* bezierPatch(float, float, vector<Point*>);
        vector<Point*> bezierPatchTriangles(int, vector<Patch*>);
        void cross(float*, float*, float*);
        void normalize(float*);
        float bezierPointTangent(float u, float v, float m[4][4] , float t[4][4], int d);
        vector<Point*> bezierTangent(int,vector<Patch*>);
};

#endif

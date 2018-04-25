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

	public:
		Vertex();
		Vertex(vector<Point*>);
		vector<Point*> getPointsList();
		void setPointsList(vector<Point*>);
		void makePlane(float);
		void makeBox(float, float, float, int);
		void makeCone(float, float, int, int);
		void makeSphere(float, int, int);
		void makeTorus(float, float, int, int);
        Point* bezierCurve(float, Point*, Point*, Point*, Point*);
        Point* bezierPatch(float, float, vector<Point*>);
        vector<Point*> bezierPatchTriangles(int, vector<Patch*>);

};

#endif

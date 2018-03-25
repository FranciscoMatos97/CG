#ifndef PROJETO_STRUCT_H__
#define PROJETO_STRUCT_H__

#include <string.h>
#include <vector>
#include "Transform.h"
#include "Point.h"

using namespace std;

class Struct{

    string file;
    vector<Transform*> refit;
    vector<Point*> points;

public:
	Struct();
	Struct(string,vector<Transform*>,vector<Point*>);
	string getFile();
	vector<Transform*> getRefit();
    vector<Point*> getPoints();
	void setFile(string);
	void setRefit(vector<Transform*>);
    void setPoints(vector<Point*>);
	void addTransform(Transform*);
	void clear();
	int size();
};

#endif

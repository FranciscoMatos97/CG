#ifndef PROJETO_TRANSFORM_H__
#define PROJETO_TRANSFORM_H__

#include <string>
#include <vector>
#include "Point.h"

using namespace std;

class Transform{

	string name;
	float timeT;
	vector<Point*> pointsL;

public:
	Transform();
	Transform(string,float,vector<Point*>);
	string getName();
	float getTime();
	vector<Point*> getPoints();
	void setName(string);
	void setTime(float);
	void setPoint(vector<Point*>);
	Transform* clone();
	
};

#endif
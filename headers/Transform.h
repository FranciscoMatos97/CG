#ifndef PROJETO_TRANSFORM_H__
#define PROJETO_TRANSFORM_H__

#include <string>
#include <vector>
#include "Point.h"

using namespace std;

class Transform{

	string name;
	float timeT, ang;
	vector<Point*> pointsL;

public:
	Transform();
	Transform(string,float,float,vector<Point*>);
	string getName();
	float getTime();
	float getAngle();
	vector<Point*> getPoints();
	void setName(string);
	void setTime(float);
	void setAngle(float);
	void setPoint(vector<Point*>);
	Transform* clone();
	
};

#endif
#ifndef PROJETO_TRANSFORM_H__
#define PROJETO_TRANSFORM_H__

#include <string>
#include "Point.h"

using namespace std;

class Transform{

	string name;
	float ang;
	Point* point;

public:
	Transform();
	Transform(string,float,Point*);
	string getName();
	float getAngle();
	Point* getPoint();
	void setName(string);
	void setAngle(float);
	void setPoint(Point*);
	Transform* clone();
	
};

#endif
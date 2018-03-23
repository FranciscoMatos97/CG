#ifndef PROJETO_TRANSFORM_H__
#define PROJETO_TRANSFORM_H__

#include <string>

using namespace std;

class Transform{

	string name;
	float angle;
	float x;
	float y;
	float z;

public:
	Transform();
	Transform(string,float,float,float,float);
	string getName();
	float getAngle();
	float getX();
	float getY();
	float getZ();
	void setName(string);
	void setAngle(float);
	void setX(float);
	void setY(float);
	void setZ(float);
	
};

#endif
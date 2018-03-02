#define __POINT_H__

#include <math.h>

using namespace std;

class Point{
	float x, y, z;

public:
	Point();
	Point(float, float, float);
	float getX();
	float getY();
	float getZ();
	void setX(float);
	void setY(float);
	void setZ(float);

};
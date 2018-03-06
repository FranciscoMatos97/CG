#ifndef PROJETO_POINT_H__
#define PROJETO_POINT_H__

class Point{

	float x;
	float y;
	float z;

	public:
		Point();
		Point(float,float,float);
		float getX();
		float getY();
		float getZ();
		void setX(float);
		void setY(float);
		void setZ(float);
};

#endif

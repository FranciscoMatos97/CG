#include "../../headers/Transform.h"

string name;
float ang, axisX, axisY, axisZ;

Transform::Transform(){
	name = "";
	ang = 0;
	axisX=0;
	axisY=0;
	axisZ=0;
}

Transform::Transform(string n, float angl, float xx, float yy, float zz){
	name = n;
	ang = angl;
	axisX = xx;
	axisY = yy;
	axisZ = zz;
}

string Transform::getName(){
	return name;
}

float Transform::getAngle(){
	return ang;
}

float Transform::getX(){
	return axisX;
}

float Transform::getY(){
	return axisY;
}

float Transform::getZ(){
	return axisZ;
}

void Transform::setName(string n){
	name = n;
}

void Transform::setAngle(float angl){
	ang = angl;
}

void Transform::setX(float xx){
	axisX = xx;
}

void Transform::setY(float yy){
	axisY = yy;
}

void Transform::setZ(float zz){
	axisZ = zz;
}
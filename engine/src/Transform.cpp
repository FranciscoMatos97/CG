#include "../../headers/Transform.h"

string name;
float ang;
Point* point;

Transform::Transform(){
	name = "";
	ang = 0;
	point = NULL;
}

Transform::Transform(string n, float angl, Point* p){
	name = n;
	ang = angl;
	point = p;
}

string Transform::getName(){
	return name;
}

float Transform::getAngle(){
	return ang;
}

Point* Transform::getPoint(){
	return point;
}

void Transform::setName(string n){
	name = n;
}

void Transform::setAngle(float angl){
	ang = angl;
}

void Transform::setPoint(Point* p){
	point = p;
}

Transform* Transform::clone(){
	return this;
}
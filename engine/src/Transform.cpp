#include "../../headers/Transform.h"

string name;
float timeT, ang;
vector<Point*> pointsL;

Transform::Transform(){
	name = "";
	ang = 0;
	timeT = 0;
}

Transform::Transform(string n, float ti, float a, vector<Point*> p){
	name = n;
	timeT = ti;
	ang = a;
	pointsL = p;
}

string Transform::getName(){
	return name;
}

float Transform::getTime(){
	return timeT;
}

float Transform::getAngle(){
	return ang;
}

vector<Point*> Transform::getPoints(){
	return pointsL;
}

void Transform::setName(string n){
	name = n;
}

void Transform::setTime(float ti){
	timeT = ti;
}

void Transform::setAngle(float a){
	ang = a;
}

void Transform::setPoint(vector<Point*> p){
	pointsL = p;
}

Transform* Transform::clone(){
	return this;
}
#include "../../headers/Transform.h"

string name;
float timeT;
vector<Point*> pointsL;

Transform::Transform(){
	name = "";
	timeT = 0;
}

Transform::Transform(string n, float ti, vector<Point*> p){
	name = n;
	timeT = ti;
	pointsL = p;
}

string Transform::getName(){
	return name;
}

float Transform::getTime(){
	return timeT;
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

void Transform::setPoint(vector<Point*> p){
	pointsL = p;
}

Transform* Transform::clone(){
	return this;
}
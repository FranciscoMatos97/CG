#include "../../headers/Struct.h"

string file;
vector<Transform*> refit;
vector<Point*> points;

Struct::Struct(){
	file = "";
}

Struct::Struct(string name, vector<Transform*> l, vector<Point*> p){
	file = name;
	refit = l;
	points = p;
}

string Struct::getFile(){
	return file;
}

vector<Transform*> Struct::getRefit(){
	return refit;
}

vector<Point*> Struct::getPoints(){
	return points;
}

void Struct::setFile(string s){
	file = s;
}

void Struct::setRefit(vector<Transform*> l){
	refit = l;
}

void Struct::setPoints(vector<Point*> p){
	points = p;
}

void Struct::addTransform(Transform* t){
	refit.push_back(t);
}

void Struct::clear(){
	file="";
	refit.clear();
	points.clear();
}

int Struct::size(){
	return (refit.size() + points.size());
}

void Struct::put(Struct s){
	refit.insert(refit.end(), s.getRefit().begin(), s.getRefit().end());
	points.insert(points.end(), s.getPoints().begin(), s.getPoints().end());
}


#include "../../headers/Struct.h"

string file;
vector<Transform*> refit;
vector<Point*> points;
GLuint buffer[1];

Struct::Struct(){
	file = "";
}

Struct::Struct(string name, vector<Transform*> l, vector<Point*> p, GLuint b){
	file = name;
	refit = l;
	points = p;
	buffer[1]=b;
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

GLuint* Struct::getBuffer(){
    return buffer;
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

void Struct::setBuffer(GLuint b){
    buffer[1] = b;
}

void Struct::addTransform(Transform* t){
	refit.push_back(t);
}

void Struct::addTransform(vector<Transform*> vt){
	refit.insert(refit.begin(), vt.begin(), vt.end());
}

void Struct::clear(){
	file="";
	refit.clear();
	points.clear();
}

int Struct::size(){
	return (refit.size() + points.size());
}

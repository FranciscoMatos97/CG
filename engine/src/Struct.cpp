#include "../../headers/Struct.h"

string file;
vector<Transform*> refit;
vector<Point*> points;
GLuint buffer[1];
float* vertex_array;

Struct::Struct(){
	file = "";
}

Struct::Struct(string name, vector<Transform*> l, vector<Point*> p, GLuint b, float* va){
	file = name;
	refit = l;
	points = p;
	buffer[0] = b;
	vertex_array = va;
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

GLuint Struct::getBuffer(){
    return buffer[0];
}

float* Struct::getVertexArray(){
	return vertex_array;
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
    buffer[0] = b;
}

void Struct::setVertexArray(float* b){
	vertex_array = b;
}

void Struct::addTransform(Transform* t){
	refit.push_back(t);
}

void Struct::addTransform(vector<Transform*> vt){
	refit.insert(refit.begin(), vt.begin(), vt.end());
}

void Struct::alocaVertexArray(){
	vertex_array = (float*) malloc(sizeof(float) * points.size() * 3);
}

void Struct::clear(){
	file="";
	refit.clear();
	points.clear();
}

int Struct::size(){
	return (refit.size() + points.size());
}

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

void Struct::clear(){
	file="";
	refit.clear();
	points.clear();
}

int Struct::size(){
	return (refit.size() + points.size());
}

void Struct::fillBuffer(){
	Point p;
	int index = 0;
	vertex_array = (float*) malloc(sizeof(float) * points.size() * 3);

	for (vector<Point *>::const_iterator i = points.begin(); i != points.end(); ++i) {
		p = **i;
		vertex_array[index] = p.getX();
		vertex_array[index+1] = p.getY();
		vertex_array[index+2] = p.getZ();
		index+=3;
	}

	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size() * 3, vertex_array, GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY);
}

void Struct::draw(){
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, points.size() * 3);
}
#ifndef PROJETO_STRUCT_H__
#define PROJETO_STRUCT_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <GL/glew.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <string.h>
#include <vector>
#include "Transform.h"
#include "Point.h"

using namespace std;

class Struct{

    string file;
    vector<Transform*> refit;
    vector<Point*> points;
    GLuint buffer[1];
    float* vertexArray;

public:
	Struct();
	Struct(string,vector<Transform*>,vector<Point*>, GLuint, float*);
	string getFile();
	vector<Transform*> getRefit();
    vector<Point*> getPoints();
    GLuint getBuffer();
	float* getVertexArray();
	void setFile(string);
	void setRefit(vector<Transform*>);
    void setPoints(vector<Point*>);
	void setBuffer(GLuint);
	void setVertexArray(float*);
	void addTransform(Transform*);
	void addTransform(vector<Transform*>);
	void alocaVertexArray();
	void clear();
	int size();
};

#endif

#include "../../headers/Struct.h"

string file3d, fileTexture;
Material material;
Light light;
vector<Transform*> refit;
vector<Point*> points, normals, textures;
GLuint buffer[3];
float *points_array, *normals_array, *textures_array;

Struct::Struct() : Light(), Material(){}

string Struct::getFile3d(){
	return file3d;
}

string Struct::getFileTexture(){
    return fileTexture;
}

Material Struct::getMaterial(){
    return material;
}

Light Struct::getLight(){
    return light;
}

vector<Transform*> Struct::getRefit(){
	return refit;
}

vector<Point*> Struct::getPoints(){
	return points;
}

vector<Point*> Struct::getNormals(){
    return normals;
}

vector<Point*> Struct::getTextures(){
    return textures;
}

GLuint Struct::getBuffer(){
    return *buffer;
}

float* Struct::getPointsArray(){
	return points_array;
}

float* Struct::getNormalsArray(){
    return normals_array;
}

float* Struct::getTexturesArray(){
    return textures_array;
}

void Struct::setFile3d(string s){
	file3d = s;
}

void Struct::setFileTexture(string s){
    fileTexture = s;
}

void Struct::setMaterial(Material m){
    material = m;
}

void Struct::setLight(Light l){
    light = l;
}

void Struct::setRefit(vector<Transform*> l){
	refit = l;
}

void Struct::setPoints(vector<Point*> p){
	points = p;
}

void Struct::setNormals(vector<Point*> n){
    normals = n;
}

void Struct::setTextures(vector<Point*> t){
    textures = t;
}

void Struct::setBuffer(GLuint b){
    *buffer = b;
}

void Struct::setPointsArray(float* p){
	points_array = p;
}

void Struct::setNormalsArray(float* n){
    normals_array = n;
}

void Struct::setTexturesArray(float* t){
    textures_array = t;
}

void Struct::addTransform(Transform* t){
	refit.push_back(t);
}

void Struct::addTransform(vector<Transform*> vt) {
    refit.insert(refit.begin(), vt.begin(), vt.end());
}

void Struct::prepareTexture() {

}

void Struct::fillBuffer(){
	Point p;
	int index = 0;

	points_array = (float*) malloc(sizeof(float) * points.size() * 3);
    normals_array = (float*) malloc(sizeof(float) * normals.size() * 3);
    textures_array = (float*) malloc(sizeof(float) * textures.size() * 3);

	for (vector<Point *>::const_iterator i = points.begin(); i != points.end(); ++i) {
		p = **i;
		points_array[index] = p.getX();
		points_array[index+1] = p.getY();
		points_array[index+2] = p.getZ();
		index+=3;
	}

    index = 0;
    for (vector<Point *>::const_iterator i = normals.begin(); i != normals.end(); ++i) {
        p = **i;
        normals_array[index] = p.getX();
        normals_array[index+1] = p.getY();
        normals_array[index+2] = p.getZ();
        index+=3;
    }

    index = 0;
    for (vector<Point *>::const_iterator i = textures.begin(); i != textures.end(); ++i) {
        p = **i;
        textures_array[index] = p.getX();
        textures_array[index+1] = p.getY();
        textures_array[index+2] = p.getZ();
        index+=3;
    }

    glGenBuffers(3, buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size() * 3, points_array, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size() * 3, normals_array, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textures.size() * 3, textures_array, GL_STATIC_DRAW);

    free(points_array); free(normals_array); free(textures_array);
}

void Struct::draw(){
    glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
    glVertexPointer(3,GL_FLOAT,0,0);

    if(normals.size()!=0){
        glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
        glNormalPointer(GL_FLOAT, 0, 0);
    }

    if(textures.size()!=0){
        glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
    }

    glDrawArrays(GL_TRIANGLES, 0, (points.size()+normals.size()+textures.size()) * 3);
}


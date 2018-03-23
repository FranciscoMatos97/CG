#include "../../headers/Struct.h"

string file;
vector<Transform*> refit;

Struct::Struct(){
	file = "";
}

Struct::Struct(string name, vector<Transform*> l){
	file = name;
	refit = l;
}

string Struct::getFile(){
	return file;
}

vector<Transform*> Struct::getRefit(){
	return refit;
}

void Struct::setFile(string s){
	file = s;
}

void Struct::setRefit(vector<Transform*> l){
	refit = l;
}


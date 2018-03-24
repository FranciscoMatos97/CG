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

void Struct::addTransform(Transform* t){
	refit.push_back(t);
}

void Struct::clear(){
	file="";
	refit.clear();
}

int Struct::size(){
	return refit.size();
}

void Struct::put(Struct s){
	refit.insert(refit.end(), s.getRefit().begin(), s.getRefit().end());
}


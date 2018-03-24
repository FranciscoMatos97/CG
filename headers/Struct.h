#ifndef PROJETO_STRUCT_H__
#define PROJETO_STRUCT_H__

#include <string.h>
#include <vector>
#include "Transform.h"

using namespace std;

class Struct{

	string file;
	vector<Transform*> refit;

public:
	Struct();
	Struct(string,vector<Transform*>);
	string getFile();
	vector<Transform*> getRefit();
	void setFile(string);
	void setRefit(vector<Transform*>);
	void addTransform(Transform*);
	void clear();
	int size();
	void put(Struct);
};

#endif

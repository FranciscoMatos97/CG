#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <stdlib.h>
#include "../../headers/vertex.h"

using namespace std;


void saveFile(vector<Point*> v, string filename){

	ofstream file;

	string f = "../files3d/" + filename; 

	file.open(f.c_str(), ios_base::app);

		for(int i=0; i<v.size(); ++i){
			file << v[i]->Point::getX() << ' ';
			file << v[i]->Point::getY() << ' ';
			file << v[i]->Point::getZ() << endl;
		}

		file << "--- New ---" << endl;

		file.close();

}

int main(int argc, char** argv){

	vector<Point*> v;

	float size=0;

	if(argc < 4){
		cout << "Not enough arguments" << endl;
	}


	if(strcmp(argv[1], "plane") == 0){

		size = atoi(argv[2]);
		v = makePlane(size);
		saveFile(v, "plane.3d");
	}

	if(strcmp(argv[1], "box") == 0 && argc == 7){
		cout << "ola" << endl;
		float x = atoi(argv[2]);
		float y = atoi(argv[3]);
		float z = atoi(argv[4]);
		int divisions = atoi(argv[5]);
		v = makeBox(x, y, z, divisions);
		saveFile(v, "box.3d");
	}

	if(strcmp(argv[1], "sphere") == 0 && argc == 6){

		float radius = atoi(argv[2]);
		int slices = atoi(argv[3]);
		int stacks = atoi(argv[4]);
		v = makeSphere(radius, slices, stacks);
		saveFile(v, "sphere.3d");
	}

	if(strcmp(argv[1], "cone") == 0 && argc == 7){

		float radius = atoi(argv[2]);
		float height = atoi(argv[3]);
		int slices = atoi(argv[4]);
		int stacks = atoi(argv[5]);
		v = makeCone(radius, height, slices, stacks);
		saveFile(v, "cone.3d");
	}

	return 0;
}



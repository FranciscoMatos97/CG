#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include "headers/Point.h"

using namespace std;


vector<Point*> makePlane(float size){

	vector<Point*> pointsList;
	float h = size/2;

	pointsList.push_back(new Point(h, 0, h));
	pointsList.push_back(new Point(h, 0, -h));
	pointsList.push_back(new Point(-h, 0, -h));

	pointsList.push_back(new Point(h, 0, h));
	pointsList.push_back(new Point(-h, 0, -h));
	pointsList.push_back(new Point(-h, 0, h));
	
	return pointsList;
}

void saveFile(vector<Point*> v, string filename){

	ofstream file;

	file.open("files3d/plane.3d", ios_base::app);


		for(int i=0; i<v.size(); ++i){
			file << v[i]->Point::getX() << ' ';
			file << v[i]->Point::getY() << ' ';
			file << v[i]->Point::getZ() << endl;
		}

		file << "--- Novo Plano ---" << endl;

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

	return 0;
}



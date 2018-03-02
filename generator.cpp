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

	string directory = "files3d/" + filename;
	ofstream file;

	file.open(directory);

	for(int i=0; i<v.size(); ++i){
		file << v[i]->Point::getX() << ' ';
		file << v[i]->Point::getY() << ' ';
		file << v[i]->Point::getZ() << ' ';
		file << '\n';
	}
	
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

		/*for (vector<Point*>::iterator it = v.begin() ; it != v.end(); ++it)
			cout << (*it)->print() << endl;
    		cout << v[i]->Point::getY() << ' ';
    		cout << v[i]->Point::getZ() << ' ';

    		cout << '\n';
		}*/
					
		saveFile(v, "plane.3d");
	}

	return 0;
}



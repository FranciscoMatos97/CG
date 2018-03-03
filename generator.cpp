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

vector<Point*> makeBox(float x, float y, float z){

	vector<Point*> pointsList;
	float nx = x/2;
	float ny = y/2;
	float nz = z/2;

	//face frontal
	pointsList.push_back(new Point(nx, -ny, nz));
	pointsList.push_back(new Point(nx, ny, nz));
	pointsList.push_back(new Point(-nx, ny, nz));

	pointsList.push_back(new Point(nx, -ny, nz));
	pointsList.push_back(new Point(-nx, ny, nz));
	pointsList.push_back(new Point(-nx, -ny, nz));

	//face traseira
	pointsList.push_back(new Point(nx, -ny, -nz));
	pointsList.push_back(new Point(-nx, -ny, -nz));
	pointsList.push_back(new Point(-nx, ny, -nz));

	pointsList.push_back(new Point(nx, -ny, -nz));
	pointsList.push_back(new Point(-nx, ny, -nz));
	pointsList.push_back(new Point(nx, ny, -nz));

	//face lateral esquerda
	pointsList.push_back(new Point(-nx, -ny, nz));
	pointsList.push_back(new Point(-nx, ny, nz));
	pointsList.push_back(new Point(-nx, ny, -nz));

	pointsList.push_back(new Point(-nx, -ny, nz));
	pointsList.push_back(new Point(-nx, ny, -nz));
	pointsList.push_back(new Point(-nx, -ny, -nz));

	//face lateral direita
	pointsList.push_back(new Point(nx, -ny, nz));
	pointsList.push_back(new Point(nx, -ny, -nz));
	pointsList.push_back(new Point(nx, ny, -nz));

	pointsList.push_back(new Point(nx, -ny, nz));
	pointsList.push_back(new Point(nx, ny, -nz));
	pointsList.push_back(new Point(nx, ny, nz));

	//base inferior
	pointsList.push_back(new Point(-nx, -ny, nz));
	pointsList.push_back(new Point(-nx, -ny, -nz));
	pointsList.push_back(new Point(nx, -ny, -nz));

	pointsList.push_back(new Point(-nx, -ny, nz));
	pointsList.push_back(new Point(nx, -ny, -nz));
	pointsList.push_back(new Point(nx, -ny, nz));

	//base superior
	pointsList.push_back(new Point(nx, ny, nz));
	pointsList.push_back(new Point(-nx, ny, -nz));
	pointsList.push_back(new Point(-nx, ny, nz));

	pointsList.push_back(new Point(nx, ny, nz));
	pointsList.push_back(new Point(nx, ny, -nz));
	pointsList.push_back(new Point(-nx, ny, -nz));
	
	return pointsList;
}

void saveFile(vector<Point*> v, string filename){

	ofstream file;

	file.open("files3d/" + filename, ios_base::app);


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

	if(strcmp(argv[1], "box") == 0){

		float x = atoi(argv[2]);
		float y = atoi(argv[3]);
		float z = atoi(argv[4]);
		v = makeBox(x, y, z);
		saveFile(v, "box.3d");
	}

	/*if(strcmp(argv[1], "sphere") == 0){

		size = atoi(argv[2]);
		v = makeSphere(size);
		saveFile(v, "sphere.3d");
	}

	if(strcmp(argv[1], "cone") == 0){

		size = atoi(argv[2]);
		v = makeCone(size);
		saveFile(v, "cone.3d");
	}*/

	return 0;
}



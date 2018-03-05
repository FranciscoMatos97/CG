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

vector<Point*> makeBox(float x, float y, float z, int divisions){

	vector<Point*> pointsList;
	float nx = x/2
	float ny = y/2;
	float nz = z/2;

	float xDiv = (float) x/divisions;
	float yDiv = (float) y/divisions;
	float zDiv = (float) z/divisions;


	for(int i=0; i<divisions; i++){
		for(int j=0; j<divisions; j++){

			//face frontal
			pointsList.push_back(new Point(-nx + (j * xDiv), ny - (i * yDiv) , nz));
			pointsList.push_back(new Point(-nx + (j * xDiv), (ny - yDiv) - (i * yDiv) , nz));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), (ny - yDiv) - (i * yDiv), nz));

			pointsList.push_back(new Point(-nx + (j * xDiv), ny - (i * yDiv) , nz));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), (ny - yDiv) - (i * yDiv), nz));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny - (i * yDiv), nz));

			//face traseira
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), (ny - yDiv) - (i * yDiv), -nz));
			pointsList.push_back(new Point(-nx + (j * xDiv), (ny - yDiv) - (i * yDiv), -nz));
			pointsList.push_back(new Point(-nx + (j * xDiv), ny - (i * yDiv), -nz));

			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), (ny - yDiv) - (i * yDiv), -nz));
			pointsList.push_back(new Point(-nx + (j * xDiv), ny - (i * yDiv) , -nz));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny - (i * yDiv), -nz));

			//face lateral esquerda
			pointsList.push_back(new Point(-nx, ny - (i * yDiv), -nz + (j * zDiv)));
			pointsList.push_back(new Point(-nx, (ny - yDiv) - (i * yDiv), -nz + (j * zDiv)));
			pointsList.push_back(new Point(-nx, (ny - yDiv) - (i * yDiv), (-nz + zDiv) + (j * zDiv)));

			pointsList.push_back(new Point(-nx, ny - (i * yDiv), -nz + (j * zDiv)));
			pointsList.push_back(new Point(-nx, (ny - yDiv) - (i * yDiv), (-nz + zDiv) + (j * zDiv)));
			pointsList.push_back(new Point(-nx, ny - (i * yDiv), (-nz + zDiv) + (j * zDiv)));

			//face lateral direita
			pointsList,push_back(new Point(nx, (ny - yDiv) - (i * yDiv), nz - (j * zDiv)));
            pointsList,push_back(new Point(nx, (ny - yDiv) - (i * yDiv), (nz - zDiv) - (j * zDiv)));
            pointsList,push_back(new Point(nx, ny - (i * yDiv), nz - (j * zDiv)));

            pointsList,push_back(new Point(nx, (ny - yDiv) - (i * yDiv), (nz - zDiv) - (j * zDiv)));
            pointsList,push_back(new Point(nx, ny - (i * yDiv), (nz - zDiv) - (j * zDiv)));
            pointsList,push_back(new Point(nx, ny - (i * yDiv), nz - (j * zDiv)));

			//base inferior
			pointsList.push_back(new Point(-nx + (j * xDiv), -ny, (-nz + zDiv) + (i * zDiv)));
			pointsList.push_back(new Point(-nx + (j * xDiv), -ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), -ny, -nz + (i * zDiv)));

			pointsList.push_back(new Point(-nx + (j * xDiv), -ny, (-nz + zDiv) + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), -ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), -ny, (-nz + zDiv) + (i * zDiv));

			//base superior
			pointsList.push_back(new Point(-nx + (j * xDiv), ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point(-nx + (j * xDiv), ny, (-nz + zDiv) + (i * zDiv));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny, (-nz + zDiv) + (i * zDiv)));

			pointsList.push_back(new Point(-nx + (j * xDiv), ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny, (-nz + zDiv) + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny, -nz + (i * zDiv)));

		}
	}
	
	
	return pointsList;
}

vector<Point*> makeCone(float radius, float height, int slices, int stacks){
	vector<Point*> pointsList;
    double alpha=(2*M_PI)/slices;
    double x1=radius, z1=0;
    double x2, z2;

    for(int i=1; i<=slices+1; i++){
        x2 = radius * sin(i * alpha);
        z2 = radius * cos(i * alpha);

        //base
        pointsList.push_back(new Point(x1, 0, z1));
	    pointsList.push_back(new Point(0, 0, 0));
	    pointsList.push_back(new Point(x2, 0, z2));

        //cone
        pointsList.push_back(new Point(0, height, 0));
	    pointsList.push_back(new Point(x1, 0, z1));
	    pointsList.push_back(new Point(x2, 0, z2));  

        x1 = x2;
        z1 = z2;
    }
	
	return pointsList;
}
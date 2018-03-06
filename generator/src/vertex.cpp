#include <vector>
#include <math.h>
#include "../../headers/Point.h"

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
	float nx = x/2;
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
			pointsList.push_back(new Point(nx, (ny - yDiv) - (i * yDiv), nz - (j * zDiv)));
            pointsList.push_back(new Point(nx, (ny - yDiv) - (i * yDiv), (nz - zDiv) - (j * zDiv)));
            pointsList.push_back(new Point(nx, ny - (i * yDiv), nz - (j * zDiv)));

            pointsList.push_back(new Point(nx, (ny - yDiv) - (i * yDiv), (nz - zDiv) - (j * zDiv)));
            pointsList.push_back(new Point(nx, ny - (i * yDiv), (nz - zDiv) - (j * zDiv)));
            pointsList.push_back(new Point(nx, ny - (i * yDiv), nz - (j * zDiv)));

			//base inferior
			pointsList.push_back(new Point(-nx + (j * xDiv), -ny, (-nz + zDiv) + (i * zDiv)));
			pointsList.push_back(new Point(-nx + (j * xDiv), -ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), -ny, -nz + (i * zDiv)));

			pointsList.push_back(new Point(-nx + (j * xDiv), -ny, (-nz + zDiv) + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), -ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), -ny, (-nz + zDiv) + (i * zDiv)));

			//base superior
			pointsList.push_back(new Point(-nx + (j * xDiv), ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point(-nx + (j * xDiv), ny, (-nz + zDiv) + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny, (-nz + zDiv) + (i * zDiv)));

			pointsList.push_back(new Point(-nx + (j * xDiv), ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny, (-nz + zDiv) + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny, -nz + (i * zDiv)));

		}
	}
	
	
	return pointsList;
}

vector<Point*> makeCone(float radius, float height, int slices, int stacks) {
    vector<Point*> pointsList;
    float alpha = (float) (2*M_PI)/slices;
    float tmp = (float) height/stacks;
    float tanB = (float) height/radius;
    float h1 = 0, h2, radius2;
    float xc1, zc1, xc2, zc2, xc3, zc3, xc4, zc4;
    int i, j;

    for(j=1; j<=stacks; j++){
        h2 = tmp * j;
        radius2 = (height-h2) / tanB;
        xc1 = radius, zc1 = 0;
        xc3 = radius2, zc3 = 0;

        if(j == 1){
            for(i=1; i<=slices+1; i++){
                xc2 = radius * sin(i * alpha);
                zc2 = radius * cos(i * alpha);
                xc4 = radius2 * sin(i * alpha);
                zc4 = radius2 * cos(i * alpha);

                //base
                pointsList.push_back(new Point(xc1,0.0f,zc1));
                pointsList.push_back(new Point(0.0f,0.0f,0.0f));
                pointsList.push_back(new Point(xc2,0.0f,zc2));
                //lados
                pointsList.push_back(new Point(xc1,0.0f,zc1));
                pointsList.push_back(new Point(xc2,0.0f,zc2));
                pointsList.push_back(new Point(xc3,h2,zc3));
                pointsList.push_back(new Point(xc2,0.0f,zc2));
                pointsList.push_back(new Point(xc4,h2,zc4));
                pointsList.push_back(new Point(xc3,h2,zc3));

                xc1 = xc2, zc1 = zc2;
                xc3 = xc4, zc3 = zc4;
            }
        }
        else if(j == stacks){
            for(i=1; i<=slices+1; i++){
                xc2 = radius * sin(i * alpha);
                zc2 = radius * cos(i * alpha);

                pointsList.push_back(new Point(0.0f,height,0.0f));
                pointsList.push_back(new Point(xc1,h1,zc1));
                pointsList.push_back(new Point(xc2,h1,zc2));

                xc1 = xc2, zc1 = zc2;
            }
        }
        else {
            for (i = 1; i <= slices + 1; i++) {
                xc2 = radius * sin(i * alpha);
                zc2 = radius * cos(i * alpha);
                xc4 = radius2 * sin(i * alpha);
                zc4 = radius2 * cos(i * alpha);

                pointsList.push_back(new Point(xc1, h1, zc1));
                pointsList.push_back(new Point(xc2, h1, zc2));
                pointsList.push_back(new Point(xc3, h2, zc3));
                pointsList.push_back(new Point(xc2, h1, zc2));
                pointsList.push_back(new Point(xc4, h2, zc4));
                pointsList.push_back(new Point(xc3, h2, zc3));

                xc1 = xc2, zc1 = zc2;
                xc3 = xc4, zc3 = zc4;
            }
        }

        h1 = h2;
        radius = radius2;
    }
    
    return pointsList;
}
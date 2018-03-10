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

vector<Point*> makeSphere(float radius, int slices, int stacks){
    vector<Point*> v;

    float h = (M_PI) / stacks;                                                                                       
    float h2 = (2 * M_PI) / slices;                                                                                  
                                                                                                                 
    //float x = radius * cos(h2) * sin(h);                                                                           
    //float y = radius * cos(h);                                                                                     
    //float z = radius * sin(h2) * sin(h);                                                                                                                                                                        
                                                                                                                     
    for (int i = 0; i < slices; i++) {                                                                               
                                                                                                                     
        for (int j = 0; j < stacks; j++) {                                                                              
                                                                                                                     
            float x2 = radius*cos((i+1)*h2)*sin(h);                                                                  
            float y2 = radius*cos(h);                                                                                
            float z2 = radius*sin((i+1)*h2)*sin(h);                                                                  

            float x3 = radius*cos(i*h2)*sin(h);                                                                      
            float y3 = radius*cos(h);                                                                                
            float z3 = radius*sin(i*h2)*sin(h);                                                                      
                                                                                                                     
            if (j == 0) {                                                                                            
                v.push_back(new Point(0, radius, 0));                                                                            
                v.push_back(new Point(radius*cos((i+1)*h2)*sin((j+1)*h), radius*cos((j+1)*h), radius*sin((i+1)*h2)*sin((j+1)*h)));
                v.push_back(new Point(radius*cos(i*h2)*sin((j+1)*h), radius*cos((j+1)*h), radius*sin(i*h2)*sin((j+1)*h)));       

            }
                                                                                       
            if(j == stacks-1){                                                               
                v.push_back(new Point(0, -radius, 0));
                v.push_back(new Point(radius*cos(i*h2)*sin((j+1)*h) + x3, -y2, radius*sin(i*h2)*sin((j+1)*h) + z3));
                v.push_back(new Point(radius*cos((i+1)*h2)*sin((j+1)*h) + x2, -y3, radius*sin((i+1)*h2)*sin((j+1)*h) + z2));     
            }                                                                                                        
                                                                                                                     
            else{                                                                                                                                                                           
                v.push_back(new Point(radius*cos((i+1)*h2)*sin((j+1)*h), radius*cos((j+1)*h), radius*sin((i+1)*h2)*sin((j+1)*h)));
                v.push_back(new Point(radius*cos((i+1)*h2)*sin((j+2)*h), radius*cos((j+2)*h), radius*sin((i+1)*h2)*sin((j+2)*h)));
                v.push_back(new Point(radius*cos(i*h2)*sin((j+1)*h), radius*cos((j+1)*h), radius*sin(i*h2)*sin((j+1)*h)));       
                                                                            
                v.push_back(new Point(radius*cos(i*h2)*sin((j+1)*h), radius*cos((j+1)*h), radius*sin(i*h2)*sin((j+1)*h)));       
                v.push_back(new Point(radius*cos((i+1)*h2)*sin((j+2)*h), radius*cos((j+2)*h), radius*sin((i+1)*h2)*sin((j+2)*h)));
                v.push_back(new Point(radius*cos(i*h2)*sin((j+2)*h), radius*cos((j+2)*h), radius*sin(i*h2)*sin((j+2)*h)));       
                                                                                                                     
            }                                                                                                        
                                                                                                                                                                                                                     
        }    
    }                                                                                                     

    return v;
}

vector<Point*> makeCone(float radius, float height, int slices, int stacks) {
    vector<Point*> pointsList;
    double alpha = (2*M_PI)/slices;
    double tmp = height/stacks;
    double tanB = height/radius;
    double h1 = 0, h2, radius2;
    float x1, x2, x3, x4, z1, z2, z3, z4;

    for(int j=1; j<=stacks; j++){
        h2 = tmp * j;
        radius2 = (height-h2) / tanB;

        for(int i=1; i<=slices+1; i++){
            x1 = radius*sin(alpha*i);
            z1 = radius*cos(alpha*i);

            x2 = radius*sin(alpha*(i+1));
            z2 = radius*cos(alpha*(i+1));

            x3 = radius2*sin(alpha*i);
            z3 = radius2*cos(alpha*i);

            x4 = radius2*sin(alpha*(i+1));
            z4 = radius2*cos(alpha*(i+1));

            if(j == 1){
                
                //base
                pointsList.push_back(new Point(0.0f,0,0.0f));
                pointsList.push_back(new Point(x2,0,z2));
                pointsList.push_back(new Point(x1,0,z1));

                //lados
                pointsList.push_back(new Point(x1,0,z1));
                pointsList.push_back(new Point(x2,0,z2));
                pointsList.push_back(new Point(x3,h2,z3));

                pointsList.push_back(new Point(x2,0,z2));
                pointsList.push_back(new Point(x4,h2,z4));
                pointsList.push_back(new Point(x3,h2,z3));

            }
            else if(j == stacks){

                pointsList.push_back(new Point(x1,h1,z1));
                pointsList.push_back(new Point(x2,h1,z2));
                pointsList.push_back(new Point(0,height,0)); 

            }
            else {

                //lados
                pointsList.push_back(new Point(x1, h1, z1));
                pointsList.push_back(new Point(x2, h1, z2));
                pointsList.push_back(new Point(x3, h2, z3));

                pointsList.push_back(new Point(x2, h1, z2));
                pointsList.push_back(new Point(x4, h2, z4));
                pointsList.push_back(new Point(x3, h2, z3));

            }
        }

        h1 = h2;
        radius = radius2;
    }
    
    return pointsList;
}
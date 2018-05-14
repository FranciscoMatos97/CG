#include "../../headers/vertex.h"

using namespace std;

Vertex::Vertex(){}

Vertex::Vertex(vector<Point*> pl, vector<Point*> nl, vector<Point*> tl){
    pointsList = pl;
    normalsList = nl;
    texturesList = tl;
}

vector<Point*> Vertex::getPointsList(){
    return pointsList;
}

vector<Point*> Vertex::getNormalsList(){
    return normalsList;
}

vector<Point*> Vertex::getTexturesList(){
    return texturesList;
}

void Vertex::setPointsList(vector<Point*> pl){
    pointsList = pl;
}

void Vertex::setNormalsList(vector<Point*> nl){
    normalsList = nl;
}

void Vertex::setTexturesList(vector<Point*> tl){
    texturesList = tl;
}

void Vertex::makePlane(float size){

	float h = size/2;


    pointsList.push_back(new Point(h, 0, h));
    pointsList.push_back(new Point(h, 0, -h));
    pointsList.push_back(new Point(-h, 0, -h));
    normalsList.push_back(new Point(0,1,0));
    normalsList.push_back(new Point(0,1,0));
    normalsList.push_back(new Point(0,1,0));
    texturesList.push_back(new Point(1,1,0));
    texturesList.push_back(new Point(1,0,0));
    texturesList.push_back(new Point(0,0,0));

    pointsList.push_back(new Point(h, 0, h));
    pointsList.push_back(new Point(-h, 0, -h));
    pointsList.push_back(new Point(-h, 0, h));
    normalsList.push_back(new Point(0,1,0));
    normalsList.push_back(new Point(0,1,0));
    normalsList.push_back(new Point(0,1,0));
    texturesList.push_back(new Point(1,1,0));
    texturesList.push_back(new Point(0,0,0));
    texturesList.push_back(new Point(0,1,0));


}

void Vertex::makeBox(float x, float y, float z, int divisions) {

	float nx = x/2;
	float ny = y/2;
	float nz = z/2;

	float xDiv = (float) x/divisions;
	float yDiv = (float) y/divisions;
	float zDiv = (float) z/divisions;

    float texY1 = z/((z*2)+y);
    float texY2 = (z+y)/((z*2)+y);

    float texX1 = (z)/((z*2)+(x*2));
    float texX2 = (z+x)/((z*2)+(x*2));
    float texX3 = ((z*2)+x)/((z*2)+(x*2));

    float texDivX = (x/((z*2)+(x*2)))/float(divisions);
    float texDivY = (y/((z*2)+y))/float(divisions);
    float texDivZ = (z/((z*2)+(x*2)))/float(divisions);

	for(int i=0; i<divisions; i++){
		for(int j=0; j<divisions; j++){

			//face frontal
			pointsList.push_back(new Point(-nx + (j * xDiv), ny - (i * yDiv) , nz));
			pointsList.push_back(new Point(-nx + (j * xDiv), (ny - yDiv) - (i * yDiv) , nz));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), (ny - yDiv) - (i * yDiv), nz));
            normalsList.push_back(new Point(0,0,1));
            normalsList.push_back(new Point(0,0,1));
            normalsList.push_back(new Point(0,0,1));
            texturesList.push_back(new Point(texX1+(j*texDivX), texY2 - (i*texDivY),0));
            texturesList.push_back(new Point(texX1+(j*texDivX),(texY2 - texDivY)-(i*texDivY),0));
            texturesList.push_back(new Point((texX1+texDivX)+(j*texDivX),(texY2-texDivY)-(i*texDivY),0));

            pointsList.push_back(new Point(-nx + (j * xDiv), ny - (i * yDiv) , nz));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), (ny - yDiv) - (i * yDiv), nz));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny - (i * yDiv), nz));
            normalsList.push_back(new Point(0,0,1));
            normalsList.push_back(new Point(0,0,1));
            normalsList.push_back(new Point(0,0,1));
            texturesList.push_back(new Point(texX1+(j*texDivX),texY2-(i*texDivY),0));
            texturesList.push_back(new Point((texX1+texDivX)+(j*texDivX),(texY2-texDivY)-(i*texDivY),0));
            texturesList.push_back(new Point((texX1+texDivX)+(j*texDivX),texY2-(i*texDivY),0));

            //face traseira
            pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), (ny - yDiv) - (i * yDiv), -nz));
			pointsList.push_back(new Point(-nx + (j * xDiv), (ny - yDiv) - (i * yDiv), -nz));
			pointsList.push_back(new Point(-nx + (j * xDiv), ny - (i * yDiv), -nz));
            normalsList.push_back(new Point(0,0,-1));
            normalsList.push_back(new Point(0,0,-1));
            normalsList.push_back(new Point(0,0,-1));
            texturesList.push_back(new Point((1-texDivX)-(j*texDivX),(texY2-texDivY)-(i*texDivY),0));
            texturesList.push_back(new Point(1-(j*texDivX),(texY2-texDivY)-(i*texDivY),0));
            texturesList.push_back(new Point(1-(j*texDivX),texY2-(i*texDivY),0));


            pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), (ny - yDiv) - (i * yDiv), -nz));
			pointsList.push_back(new Point(-nx + (j * xDiv), ny - (i * yDiv) , -nz));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny - (i * yDiv), -nz));
            normalsList.push_back(new Point(0,0,-1));
            normalsList.push_back(new Point(0,0,-1));
            normalsList.push_back(new Point(0,0,-1));
            texturesList.push_back(new Point((1-texDivX)-(j*texDivX),(texY2-texDivY)-(i*texDivY),0));
            texturesList.push_back(new Point(1-(j*texDivX),texY2-(i*texDivY),0));
            texturesList.push_back(new Point((1-texDivX)-(j*texDivX),texY2-(i*texDivY),0));


            //face lateral esquerda
            pointsList.push_back(new Point(-nx, ny - (i * yDiv), -nz + (j * zDiv)));
			pointsList.push_back(new Point(-nx, (ny - yDiv) - (i * yDiv), -nz + (j * zDiv)));
			pointsList.push_back(new Point(-nx, (ny - yDiv) - (i * yDiv), (-nz + zDiv) + (j * zDiv)));
            normalsList.push_back(new Point(-1,0,0));
            normalsList.push_back(new Point(-1,0,0));
            normalsList.push_back(new Point(-1,0,0));
            texturesList.push_back(new Point((j*texDivZ),texY2-(i*texDivY),0));
            texturesList.push_back(new Point(j*texDivZ,(texY2-texDivY)-(i*texDivY),0));
            texturesList.push_back(new Point(texDivZ+(j*texDivZ),(texY2-texDivY)-(i*texDivY),0));


            pointsList.push_back(new Point(-nx, ny - (i * yDiv), -nz + (j * zDiv)));
			pointsList.push_back(new Point(-nx, (ny - yDiv) - (i * yDiv), (-nz + zDiv) + (j * zDiv)));
			pointsList.push_back(new Point(-nx, ny - (i * yDiv), (-nz + zDiv) + (j * zDiv)));
            normalsList.push_back(new Point(-1,0,0));
            normalsList.push_back(new Point(-1,0,0));
            normalsList.push_back(new Point(-1,0,0));
            texturesList.push_back(new Point((j*texDivZ),texY2-(i*texDivY),0));
            texturesList.push_back(new Point(texDivZ+(j*texDivZ),(texY2-texDivY)-(i*texDivY),0));
            texturesList.push_back(new Point(texDivZ+(j*texDivZ),texY2-(i*texDivY),0));

            //face lateral direita
            pointsList.push_back(new Point(nx, (ny - yDiv) - (i * yDiv), nz - (j * zDiv)));
            pointsList.push_back(new Point(nx, (ny - yDiv) - (i * yDiv), (nz - zDiv) - (j * zDiv)));
            pointsList.push_back(new Point(nx, ny - (i * yDiv), nz - (j * zDiv)));
            normalsList.push_back(new Point(1,0,0));
            normalsList.push_back(new Point(1,0,0));
            normalsList.push_back(new Point(1,0,0));
            texturesList.push_back(new Point(texX2+(j*texDivZ),(texY2-texDivY)-(i*texDivY),0));
            texturesList.push_back(new Point((texX2+texDivZ)-(j*texDivX),(texY2-texDivY)-(i*texDivY),0));
            texturesList.push_back(new Point(texX2+(j*texDivZ),texY2-(i*texDivY),0));

            pointsList.push_back(new Point(nx, (ny - yDiv) - (i * yDiv), (nz - zDiv) - (j * zDiv)));
            pointsList.push_back(new Point(nx, ny - (i * yDiv), (nz - zDiv) - (j * zDiv)));
            pointsList.push_back(new Point(nx, ny - (i * yDiv), nz - (j * zDiv)));
            normalsList.push_back(new Point(1,0,0));
            normalsList.push_back(new Point(1,0,0));
            normalsList.push_back(new Point(1,0,0));
            texturesList.push_back(new Point((texX2+texDivZ)+(j*texDivZ),(texY2-texDivY)-(i*texDivY),0));
            texturesList.push_back(new Point((texX2+texDivZ)+(j*texDivX),texY2-(i*texDivY),0));
            texturesList.push_back(new Point(texX2+(j*texDivZ),texY2-(i*texDivY),0));


            //base inferior
            pointsList.push_back(new Point(-nx + (j * xDiv), -ny, (-nz + zDiv) + (i * zDiv)));
			pointsList.push_back(new Point(-nx + (j * xDiv), -ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), -ny, -nz + (i * zDiv)));
            normalsList.push_back(new Point(0,-1,0));
            normalsList.push_back(new Point(0,-1,0));
            normalsList.push_back(new Point(0,-1,0));
            texturesList.push_back(new Point(texX1+(j*texDivX),(texY1-texDivZ)-(i*texDivZ),0));
            texturesList.push_back(new Point(texX1+(j*texDivX),texY1-(i*texDivZ),0));
            texturesList.push_back(new Point((texX1+texDivX)+(j*texDivX),texY1-(i*texDivZ),0));

            pointsList.push_back(new Point(-nx + (j * xDiv), -ny, (-nz + zDiv) + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), -ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), -ny, (-nz + zDiv) + (i * zDiv)));
            normalsList.push_back(new Point(0,-1,0));
            normalsList.push_back(new Point(0,-1,0));
            normalsList.push_back(new Point(0,-1,0));
            texturesList.push_back(new Point(texX1+(j*texDivX),(texY1-texDivZ)-(i*texDivZ),0));
            texturesList.push_back(new Point((texX1+texDivX)+(j*texDivX),texY1-(i*texDivZ),0));
            texturesList.push_back(new Point((texX1+texDivX)+(j*texDivX),(texY1-texDivZ)-(i*texDivZ),0));

            //base superior
            pointsList.push_back(new Point(-nx + (j * xDiv), ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point(-nx + (j * xDiv), ny, (-nz + zDiv) + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny, (-nz + zDiv) + (i * zDiv)));
            normalsList.push_back(new Point(0,1,0));
            normalsList.push_back(new Point(0,1,0));
            normalsList.push_back(new Point(0,1,0));
            texturesList.push_back(new Point(texX1+(j*texDivX),1-(i*texDivZ),0));
            texturesList.push_back(new Point(texX1+(j*texDivX),(1-texDivZ)-(i*texDivZ),0));
            texturesList.push_back(new Point((texX1+texDivX)+(j*texDivX),(1-texDivZ)-(i*texDivZ),0));

			pointsList.push_back(new Point(-nx + (j * xDiv), ny, -nz + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny, (-nz + zDiv) + (i * zDiv)));
			pointsList.push_back(new Point((-nx + xDiv) + (j * xDiv), ny, -nz + (i * zDiv)));
            normalsList.push_back(new Point(0,1,0));
            normalsList.push_back(new Point(0,1,0));
            normalsList.push_back(new Point(0,1,0));
            texturesList.push_back(new Point(texX1+(j*texDivX),1-(i*texDivZ),0));
            texturesList.push_back(new Point((texX1+texDivX)+(j*texDivX),(1-texDivZ)-(i*texDivZ),0));
            texturesList.push_back(new Point((texX1+texDivX)+(j*texDivX),1-(i*texDivZ),0));
		}
	}


}

void Vertex::makeSphere(float radius, int slices, int stacks){

    vector<Point*> v;
    float texDivY = 1.0/stacks;
    float texDivX = 1.0/slices;
    float texYcima, texYbaixo;
    float texXesq = 0, texXdir = 0+texDivX;

    float h = (M_PI) / stacks;                                                                                       
    float h2 = (2 * M_PI) / slices;
                                                                                                                     
    for (int i = 0; i < slices ; i++, texXesq+=texDivX, texXdir+=texDivX) {

        for (int j = 0; j < stacks; j++) {

            float x2 = radius*cos((i+1)*h2)*sin(h);
            float y2 = radius*cos(h);                                                                                
            float z2 = radius*sin((i+1)*h2)*sin(h);

            float x3 = radius*cos(i*h2)*sin(h);
            float y3 = radius*cos(h);                                                                                
            float z3 = radius*sin(i*h2)*sin(h);
                                                                                                                     
            if (j == 0) {
                texYcima = 1.0;
                texYbaixo = 1.0-texDivY;

                pointsList.push_back(new Point(0, radius, 0));                                                                            
                pointsList.push_back(new Point(radius*cos((i+1)*h2)*sin((j+1)*h), radius*cos((j+1)*h), radius*sin((i+1)*h2)*sin((j+1)*h)));
                pointsList.push_back(new Point(radius*cos(i*h2)*sin((j+1)*h), radius*cos((j+1)*h), radius*sin(i*h2)*sin((j+1)*h)));
                normalsList.push_back(new Point(0,1,0));
                normalsList.push_back(new Point(sin((i+1)*h2),cos((j+1)*h),cos((i+1)*h2)));
                normalsList.push_back(new Point(sin(i*h2),cos((j+1)*h),cos(i*h2)));
                texturesList.push_back(new Point(texXdir,texYbaixo,0));
                texturesList.push_back(new Point(texXesq,texYbaixo,0));
                texturesList.push_back(new Point(texXesq+texDivX/2,texYcima,0));
            }
                                                                                       
            if(j == stacks-1){
                texYcima = 0.0+texDivY;
                texYbaixo = 0.0;

                pointsList.push_back(new Point(0, -radius, 0));
                pointsList.push_back(new Point(radius*cos(i*h2)*sin((j+1)*h) + x3, -y2, radius*sin(i*h2)*sin((j+1)*h) + z3));
                pointsList.push_back(new Point(radius*cos((i+1)*h2)*sin((j+1)*h) + x2, -y3, radius*sin((i+1)*h2)*sin((j+1)*h) + z2));
                normalsList.push_back(new Point(0,-1,0));
                normalsList.push_back(new Point(sin(i*h2),-cos(h),cos(i*h2)));
                normalsList.push_back(new Point(sin((i+1)*h2),-cos(h),cos((i+1)*h2)));
                texturesList.push_back(new Point(texXesq,texYcima,0));
                texturesList.push_back(new Point(texXdir,texYcima,0));
                texturesList.push_back(new Point(texXesq+texDivX/2,texYbaixo,0));
            }                                                                                                        
                                                                                                                     
            else{
                texYcima = 1.0-j*texDivY;
                texYbaixo = 1.0-(j+1.0)*texDivY;

                pointsList.push_back(new Point(radius*cos((i+1)*h2)*sin((j+1)*h), radius*cos((j+1)*h), radius*sin((i+1)*h2)*sin((j+1)*h)));
                pointsList.push_back(new Point(radius*cos((i+1)*h2)*sin((j+2)*h), radius*cos((j+2)*h), radius*sin((i+1)*h2)*sin((j+2)*h)));
                pointsList.push_back(new Point(radius*cos(i*h2)*sin((j+1)*h), radius*cos((j+1)*h), radius*sin(i*h2)*sin((j+1)*h)));
                normalsList.push_back(new Point(sin((i+1)*h2),cos((j+1)*h),cos((i+1)*h2)));
                normalsList.push_back(new Point(sin((i+1)*h2),cos((j+2)*h),cos((i+1)*h2)));
                normalsList.push_back(new Point(sin(i*h2),cos((j+1)*h),cos(i*h2)));
                texturesList.push_back(new Point(texXdir,texYcima,0));
                texturesList.push_back(new Point(texXdir,texYbaixo,0));
                texturesList.push_back(new Point(texXesq,texYcima,0));


                pointsList.push_back(new Point(radius*cos(i*h2)*sin((j+1)*h), radius*cos((j+1)*h), radius*sin(i*h2)*sin((j+1)*h)));       
                pointsList.push_back(new Point(radius*cos((i+1)*h2)*sin((j+2)*h), radius*cos((j+2)*h), radius*sin((i+1)*h2)*sin((j+2)*h)));
                pointsList.push_back(new Point(radius*cos(i*h2)*sin((j+2)*h), radius*cos((j+2)*h), radius*sin(i*h2)*sin((j+2)*h)));
                normalsList.push_back(new Point(sin(i*h2),cos((j+1)*h),cos(i*h2)));
                normalsList.push_back(new Point(sin((i+1)*h2),cos((j+2)*h),cos((i+1)*h2)));
                normalsList.push_back(new Point(sin(i*h2),cos((j+2)*h),cos(i*h2)));
                texturesList.push_back(new Point(texXesq,texYcima,0));
                texturesList.push_back(new Point(texXdir,texYbaixo,0));
                texturesList.push_back(new Point(texXesq,texYbaixo,0));

            }
        }
    }
}

void Vertex::makeCone(float radius, float height, int slices, int stacks) {
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
    
}

void Vertex::makeTorus(float intRadius, float extRadius, int slices, int stacks){
    double angleSlice = (2*M_PI)/stacks;
    double angleStack = (2*M_PI)/slices;
    double act, next, actSt, nextSt;
    float actStR, actStZ, nextStR, nextStZ;
    float texSide = float(1)/float(slices);
    float texRing = float(1)/float(stacks);
    for(int i=0; i<stacks; i++){

        act = angleSlice * i; //a0
        next = act + angleSlice; // a1

        float x0 = cos(act);
        float y0 = sin(act);
        float x1 = cos(next);
        float y1 = sin(next);

        for(int j=0; j<slices+1; j++){


            actSt = angleStack * j;
            actStR = intRadius * cos(actSt) + extRadius;
            actStZ = intRadius * sin(actSt);

            nextSt = (j+1) * angleStack;
            nextStR = intRadius * cos(nextSt) + extRadius;
            nextStZ = intRadius * sin(nextSt);

            pointsList.push_back(new Point(cos(act)*actStR, sin(act)*actStR, actStZ));
            pointsList.push_back(new Point(cos(next)*actStR, sin(next)*actStR, actStZ));
            pointsList.push_back(new Point(cos(act)*nextStR, sin(act)*nextStR, nextStZ));
            normalsList.push_back(new Point(cos(act)*cos(actSt),sin(act)*cos(actSt),sin(actSt)));
            normalsList.push_back(new Point(cos(next)*cos(actSt),sin(next)*cos(actSt),sin(actSt)));
            normalsList.push_back(new Point(cos(act)*cos(actSt),sin(act)*cos(actSt),sin(nextSt)));
            texturesList.push_back(new Point(i*texRing,j*texSide,0));
            texturesList.push_back(new Point((i+1)*texRing,j*texRing,0));
            texturesList.push_back(new Point(i*texRing,(j+1)*texSide,0));


            pointsList.push_back(new Point(cos(act)*nextStR, sin(act)*nextStR, nextStZ));
            pointsList.push_back(new Point(cos(next)*actStR, sin(next)*actStR, actStZ));
            pointsList.push_back(new Point(cos(next)*nextStR, sin(next)*nextStR, nextStZ));
            normalsList.push_back(new Point(cos(act)*cos(nextSt),sin(act)*cos(nextSt),sin(nextSt)));
            normalsList.push_back(new Point(cos(next)*cos(actSt),sin(next)*cos(actSt),sin(actSt)));
            normalsList.push_back(new Point(cos(next)*cos(nextSt),sin(next)*cos(nextSt),sin(nextSt)));
            texturesList.push_back(new Point(i*texRing,(j+1)*texSide,0));
            texturesList.push_back(new Point((i+1)*texRing,j*texSide,0));
            texturesList.push_back(new Point((i+1)*texRing,(j+1)*texSide,0));

        }
    }

}
/**
 * Ponto da curva consoante o valor T
 */
Point* Vertex::bezierCurve(float t, Point* p0, Point* p1, Point* p2, Point* p3) {
    float x, y, z;

    float b0 = (1.0 - t) * (1.0 - t) * (1.0 - t);
    float b1 = 3 * t * (1.0 - t) * (1.0 - t);
    float b2 = 3 * t * t * (1.0 - t);
    float b3 = t * t * t;

    x = b0*p0->getX() + b1*p1->getX() + b2*p2->getX() + b3*p3->getX();
    y = b0*p0->getY() + b1*p1->getY() + b2*p2->getY() + b3*p3->getY();
    z = b0*p0->getZ() + b1*p1->getZ() + b2*p2->getZ() + b3*p3->getZ();

    Point* new_point = new Point(x, y, z);
    return new_point;
}


/**
 * Ponto da curva consoante o valor U e V
 */
Point* Vertex::bezierPatch(float u, float v, vector<Point*> control_points) {
    float matU[4][3], matUV[4][3];
    int i, j=0, k=0;

    for (i = 0; i < 16; i ++) {
        matU[j][0] = control_points[i]->getX();
        matU[j][1] = control_points[i]->getY();
        matU[j][2] = control_points[i]->getZ();

        j++;

        if (j % 4 == 0) {
            Point* pointU = bezierCurve(u, new Point(matU[0][0],matU[0][1],matU[0][2]),
                                           new Point(matU[1][0],matU[1][1],matU[1][2]),
                                           new Point(matU[2][0],matU[2][1],matU[2][2]),
                                           new Point(matU[3][0],matU[3][1],matU[3][2]));

            matUV[k][0] = pointU->getX();
            matUV[k][1] = pointU->getY();
            matUV[k][2] = pointU->getZ();

            k++;
            j = 0;
        }
    }

    Point* pointUV = bezierCurve(v, new Point(matUV[0][0],matUV[0][1],matUV[0][2]),
                                  new Point(matUV[1][0],matUV[1][1],matUV[1][2]),
                                  new Point(matUV[2][0],matUV[2][1],matUV[2][2]),
                                  new Point(matUV[3][0],matUV[3][1],matUV[3][2]));

    return pointUV;
}

/**
 * triangulos de bezier para o engine
 */
vector<Point*> Vertex::bezierPatchTriangles(int divs, vector<Patch*> patch_list){

    vector<Point*> point_list;
    float u, uu, v, vv;
    float inc = 1.0 / divs;

    for(int n_patches = 0; n_patches < patch_list.size(); n_patches++){
        vector<Point*> control_points = patch_list[n_patches]->getControlPoints();

        for(int j=0; j <= divs ; j++){
            for(int i=0; i <= divs; i++){

                u = i * inc;
                v = j * inc;
                uu = (i+1) * inc;
                vv = (j+1) * inc;

                Point* p0 = bezierPatch(u, v, control_points);
                Point* p1 = bezierPatch(u, vv, control_points);
                Point* p2 = bezierPatch(uu, v, control_points);
                Point* p3 = bezierPatch(uu, vv, control_points);

                point_list.push_back(p0);
                point_list.push_back(p2);
                point_list.push_back(p3);

                point_list.push_back(p0);
                point_list.push_back(p3);
                point_list.push_back(p1);
            }
        }
    }

    return point_list;
}

void Vertex::cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}


void Vertex::normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}

float Vertex::bezierPointTangent(float u, float v, float m[4][4] , float t[4][4], int d) {
    float pValue = 0;
    float o[4], p[4];

    //derivada de u
    if(d == 0){
        //bu*M
        for(int i = 0; i<4; i++){
            o[i] = (3 * powf(u,2.0)*m[0][i]) + (2*u*m[1][i]) + (1*m[2][i]);
        }
    } else {
        for(int i = 0; i<4; i++){
            p[i] = (powf(u,3.0)*m[0][i]) + (powf(u,2.0)*m[1][i]) + (u*m[2][i]) + m[3][i];
        }
    }

    //(bu*M)*P
    for(int i = 0; i<4; i++){
        p[i] = (p[0]*t[0][i]) + (p[1]*t[1][i]) + (p[2]*t[2][i]) + (p[3]*t[3][i]);
    }

    //((bu*M)*P)*MT
    for(int i = 0; i<4; i++){
        p[i] = (p[0]*m[0][i]) + (p[1]*m[1][i]) + (p[2]*m[2][i]) + (p[3]*m[3][i]);
    }

    if(d == 0) {
        //(((bu*M)*P)*MT)*bv
        pValue = p[0] * powf(v,3.0);
        pValue += p[1] * powf(v,2.0);
        pValue += p[2] * v;
        pValue += p[3];
        //derivada de v
    } else {
        //(((bu*M)*P)*MT)*bv
        pValue = p[0] * (3 * powf(v,2.0));
        pValue += p[1] * (2 * v);
        pValue += p[2];
    }

    return pValue;
}





vector<Point*> Vertex::bezierTangent(int tess,vector<Patch*> patchList){
    vector<Point*> derivada;
    int i, j, aux;
    float * ma[16], mT[3][16], px[4][4], py[4][4], pz[4][4], matU[3], matV[3], res[3];
    float u, v, u2, v2, level = (float)1.0/(float)tess;

    for(int patches = 0; patches < patchList.size(); patches++){
        vector<Point*> control_points = patchList[patches]->getControlPoints();
        aux = 0;

        for(i = 0; i < 4; i++){
            for( j = 0; j < 4; j++, aux++){
                px[i][j] = control_points[aux]->getX();
                py[i][j] = control_points[aux]->getY();
                pz[i][j] = control_points[aux]->getZ();
            }
        }

        //Matriz M
        float m[4][4] = {{-1, 3, -3, 1},
                         {3, -6, 3, 0 },
                         {-3, 3, 0, 0},
                         {1, 0, 0, 0}};



        for( i = 0; i<=tess ; i++){
            u = i * level;
            u2 = (i+1) * level;

            for(j = 0; j<=tess ; j++){
                v = j * level;
                v2 = (j+1) * level;

                matU[0] = bezierPointTangent(u, v, m, px,0);
                matU[1] = bezierPointTangent(u, v, m, py,0);
                matU[2] = bezierPointTangent(u, v, m, pz,0);
                normalize(matU);
                matV[0] = bezierPointTangent(u, v, m, px,1);
                matV[1] = bezierPointTangent(u, v, m, py,1);
                matV[2] = bezierPointTangent(u, v, m, pz,1);
                normalize(matV);
                cross(matV,matU,res);
                derivada.push_back(new Point(res[0],res[1],res[2]));

                matU[0] = bezierPointTangent(u2,v, m, px,0);
                matU[1] = bezierPointTangent(u2,v, m, py,0);
                matU[2] = bezierPointTangent(u2,v, m, pz,0);
                normalize(matU);
                matV[0] = bezierPointTangent(u2,v, m, px,1);
                matV[1] = bezierPointTangent(u2,v, m, py,1);
                matV[2] = bezierPointTangent(u2,v, m, pz,1);
                normalize(matV);
                cross(matV,matU,res);
                derivada.push_back(new Point(res[0],res[1],res[2]));

                matU[0] = bezierPointTangent(u2,v2, m, px,0);
                matU[1] = bezierPointTangent(u2,v2, m, py,0);
                matU[2] = bezierPointTangent(u2,v2, m, pz,0);
                normalize(matU);
                matV[0] = bezierPointTangent(u2,v2, m, px,1);
                matV[1] = bezierPointTangent(u2,v2, m, py,1);
                matV[2] = bezierPointTangent(u2,v2, m, pz,1);
                normalize(matV);
                cross(matV,matU,res);
                derivada.push_back(new Point(res[0],res[1],res[2]));

                matU[0] = bezierPointTangent(u, v, m, px,0);
                matU[1] = bezierPointTangent(u, v, m, py,0);
                matU[2] = bezierPointTangent(u, v, m, pz,0);
                normalize(matU);
                matV[0] = bezierPointTangent(u, v, m, px,1);
                matV[1] = bezierPointTangent(u, v, m, py,1);
                matV[2] = bezierPointTangent(u, v, m, pz,1);
                normalize(matV);
                cross(matV,matU,res);
                derivada.push_back(new Point(res[0],res[1],res[2]));

                matU[0] = bezierPointTangent(u2,v2, m, px,0);
                matU[1] = bezierPointTangent(u2,v2, m, py,0);
                matU[2] = bezierPointTangent(u2,v2, m, pz,0);
                normalize(matU);
                matV[0] = bezierPointTangent(u2,v2, m, px,1);
                matV[1] = bezierPointTangent(u2,v2, m, py,1);
                matV[2] = bezierPointTangent(u2,v2, m, pz,1);
                normalize(matV);
                cross(matV,matU,res);
                derivada.push_back(new Point(res[0],res[1],res[2]));

                matU[0] = bezierPointTangent(u,v2, m, px,0);
                matU[1] = bezierPointTangent(u,v2, m, py,0);
                matU[2] = bezierPointTangent(u,v2, m, pz,0);
                normalize(matU);
                matV[0] = bezierPointTangent(u,v2, m, px,1);
                matV[1] = bezierPointTangent(u,v2, m, py,1);
                matV[2] = bezierPointTangent(u,v2, m, pz,1);
                normalize(matV);
                cross(matV,matU,res);
                derivada.push_back(new Point(res[0],res[1],res[2]));
            }
        }
    }
    return derivada;
}













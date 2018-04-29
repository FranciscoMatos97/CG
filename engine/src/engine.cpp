#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <cmath>

#include "../../headers/Point.h"
#include "../../headers/Struct.h"
#include "../../headers/Parser.h"

using namespace std;

vector<Struct> estruturas;

float xr=0, yr=0, zr=0;
float angle=0;
float xt=0, yt=0, zt=0;
float cx=M_PI_4, cz=M_PI_4;
float r = 250.0;


void changeSize(int w, int h) {
// Prevent a divide by zero, when window is too short
// (you cant make a window with zero width).
    if(h == 0)
        h = 1;

// compute window's aspect ratio
    float ratio = w * 1.0 / h;

// Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
// Load Identity Matrix
    glLoadIdentity();

// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

// Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

// return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


void buildRotMatrix(float *x, float *y, float *z, float *m) {
    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float *a, float *b, float *res) {
    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}


void normalize(float *a) {
    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}


float length(float *v) {
	float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return res;
}


void multMatrixVector(float *m, float *v, float *res) {
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }
}


void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {
    //catmull-rom matrix
    float m[4][4] = {{-0.5f,  1.5f, -1.5f,  0.5f},
                     { 1.0f, -2.5f,  2.0f, -0.5f},
                     {-0.5f,  0.0f,  0.5f,  0.0f},
                     { 0.0f,  1.0f,  0.0f,  0.0f}};

    // Compute A = M * P
    float X[4] = {p0[0], p1[0], p2[0], p3[0]};
    float Y[4] = {p0[1], p1[1], p2[1], p3[1]};
    float Z[4] = {p0[2], p1[2], p2[2], p3[2]};

    float Ax[4], Ay[4], Az[4];
    multMatrixVector(*m, X, Ax);
    multMatrixVector(*m, Y, Ay);
    multMatrixVector(*m, Z, Az);
    
    // Compute pos = T * A
    float T[4] = {t*t*t, t*t, t, 1};

    pos[0] = T[0] * Ax[0] + T[1] * Ax[1] + T[2] * Ax[2] + T[3] * Ax[3];
    pos[1] = T[0] * Ay[0] + T[1] * Ay[1] + T[2] * Ay[2] + T[3] * Ay[3];
    pos[2] = T[0] * Az[0] + T[1] * Az[1] + T[2] * Az[2] + T[3] * Az[3];

    // compute deriv = T' * A
    float T_d[4] = {3*t*t, 2*t, 1, 0 };

    deriv[0] = T_d[0] * Ax[0] + T_d[1] * Ax[1] + T_d[2] * Ax[2] + T_d[3] * Ax[3];
    deriv[1] = T_d[0] * Ay[0] + T_d[1] * Ay[1] + T_d[2] * Ay[2] + T_d[3] * Ay[3];
    deriv[2] = T_d[0] * Az[0] + T_d[1] * Az[1] + T_d[2] * Az[2] + T_d[3] * Az[3];
}


// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, float* p, int POINT_COUNT) {
    float t = gt * POINT_COUNT; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
    indices[1] = (indices[0]+1)%POINT_COUNT;
    indices[2] = (indices[1]+1)%POINT_COUNT;
    indices[3] = (indices[2]+1)%POINT_COUNT;

    getCatmullRomPoint(t, p+indices[0]*3, p+indices[1]*3, p+indices[2]*3, p+indices[3]*3, pos, deriv);
}


void renderCatmullRomCurve(float* p, int POINT_COUNT) {
    float pos[3];
    float deriv[3];

    glBegin(GL_LINE_LOOP);
    for (float gt = 0; gt <= 1; gt += 0.01) {
        getGlobalCatmullRomPoint(gt, pos, deriv, p, POINT_COUNT);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
}


void orbitaCatmullRom(vector<Point*> vp, float gr){
    int POINT_COUNT = vp.size();
    float p[POINT_COUNT][3];
    float Y[3] = { 0, 1, 0 }, Z[3], M[16], pos[3], deriv[3];

    for (int i = 0; i < POINT_COUNT; ++i) {
        p[i][0] = vp.at(i)->getX();
        p[i][1] = vp.at(i)->getY();
        p[i][2] = vp.at(i)->getZ();
    }

    renderCatmullRomCurve(*p,POINT_COUNT);

    getGlobalCatmullRomPoint(gr, pos, deriv, *p, POINT_COUNT);
    glTranslatef(pos[0], pos[1], pos[2]);

    cross(deriv, Y, Z);
    cross(Z, deriv, Y);

    normalize(deriv);
    normalize(Z);
    normalize(Y);

    buildRotMatrix(deriv, Y, Z, M);
    glMultMatrixf(M);
}


void figuraPrimitiva(Struct s){

    vector<Transform*> vt = s.getRefit();
    const char* nameTransf;
    float timeT, angle, x, y, z, te, gr;
    bool cor=false;

    glPushMatrix();

    for (vector<Transform *>::const_iterator t = vt.begin(); t != vt.end(); t++) {
        nameTransf = (*t)->Transform::getName().c_str();

        if(strcmp(nameTransf,"translate")){
            x = (*t)->Transform::getPoint()->Point::getX();
            y = (*t)->Transform::getPoint()->Point::getY();
            z = (*t)->Transform::getPoint()->Point::getZ();

            if (!strcmp(nameTransf,"rotate")) {
                timeT = (*t)->Transform::getTime();
                angle = (*t)->Transform::getAngle();
                if(angle!=0){
                    glRotatef(angle,x,y,z);
                }
                else {
                    float te = glutGet(GLUT_ELAPSED_TIME)/100.f;
                    float gr = (te*360) / (timeT * 1000);
                    glRotatef(gr,x,y,z);
                }
            }
            else if (!strcmp(nameTransf,"scale")) {
                glScalef(x,y,z);
            }
            else if (!strcmp(nameTransf,"color")) {
                glColor3f(x,y,z);
                cor=true;
            }
        }
        else{
            timeT = (*t)->Transform::getTime();
            if(timeT==0){
                x = (*t)->Transform::getPoint()->Point::getX();
                y = (*t)->Transform::getPoint()->Point::getY();
                z = (*t)->Transform::getPoint()->Point::getZ();

                glTranslatef(x,y,z);
            }
            else{
                te = glutGet(GLUT_ELAPSED_TIME) % (int)(timeT * 1000);
                gr = te / (timeT * 1000);
                glColor3f(1,1,1);
                orbitaCatmullRom((*t)->Transform::getPoints(), gr);
            }
        }
    }

    float a, b, c;

    if(cor==false) {
        srand(1024);

        a = (float) rand() / (float) RAND_MAX;
        b = (float) rand() / (float) RAND_MAX;
        c = (float) rand() / (float) RAND_MAX;

        if (a <= 0.1 && b <= 0.1 && c <= 0.1) a = 1;

        glColor3f(a, b, c);
    }

    s.draw();

    glPopMatrix();
}


void renderScene(void) {
// clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// set the camera
    glLoadIdentity();
    gluLookAt((r*cos(cx)*cos(cz)),(r*sin(cz)),(r*cos(cz)*sin(cx)),
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

// put the geometric transformations here
    glRotatef(angle,xr,yr,zr);
    glTranslatef(xt,yt,zt);

// put drawing instructions here
    Struct s;

    for(vector<Struct>::const_iterator f = estruturas.begin(); f != estruturas.end(); f++) {
        s = (*f);
        figuraPrimitiva(s);
    }

// End of frame
    glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {
    float inc=0.1;

// put code to process regular keys in here
    if(key == 27){
        exit(0);
    }

    if(key == 'z'){
        zt++;
        glutPostRedisplay();
    }

    if(key == 'x'){
        zt--;
        glutPostRedisplay();
    }

    if(key=='a'){
        xr=0;
        yr=0;
        zr=0;
        angle=0;
        glutPostRedisplay();
    }

    if(key == 'b'){
        cx=M_PI_4;
        cz=M_PI_4;
        r = 250;
    }

    //zoom in
    if(key == 'i'){
        r+=2.5;
        glutPostRedisplay();
    }

    //zoom out
    if(key == 'k'){
        r-=2.5;
        glutPostRedisplay();
    }

    //esquerda
    if(key=='u'){
        cx+=inc;
        glutPostRedisplay();
    }
    //direita
    if(key=='o'){
        cx-=inc;
        glutPostRedisplay();
    }

    if(key=='m'){
        cz+=inc;
        if(cz>1.5)
            cz=1.5;
        glutPostRedisplay();
    }

    if(key=='n'){
        cz-=inc;
        if(cz<-1.5)
            cz=-1.5;
        glutPostRedisplay();
    }

    if(key == 'q'){
        angle--;
        xr--;
        glutPostRedisplay();
    }

    if(key == 'w'){
        angle++;
        xr++;
        glutPostRedisplay();
    }

    if(key == 'e'){
        angle--;
        yr--;
        glutPostRedisplay();
    }

    if(key == 'r'){
        angle++;
        yr++;
        glutPostRedisplay();
    }

    if(key == 't'){
        angle--;
        zr--;
        glutPostRedisplay();
    }

    if(key == 'y'){
        angle++;
        zr++;
        glutPostRedisplay();
    }

    if(key == 'l'){
        glPolygonMode(GL_FRONT,GL_LINE);
        glutPostRedisplay();
    }

    if(key == 'f'){
        glPolygonMode(GL_FRONT,GL_FILL);
        glutPostRedisplay();
    }

    if(key == 'p'){
        glPolygonMode(GL_FRONT,GL_POINT);
        glutPostRedisplay();
    }
}


void processSpecialKeys(int key, int xx, int yy) {
// put code to process special keys in here
    if(key == GLUT_KEY_LEFT){
        xt--;
        glutPostRedisplay();
    }

    if(key == GLUT_KEY_RIGHT){
        xt++;
        glutPostRedisplay();
    }

    if(key == GLUT_KEY_UP){
        yt++;
        glutPostRedisplay();
    }

    if(key == GLUT_KEY_DOWN){
        yt--;
        glutPostRedisplay();
    }
}


void showHelp(){
    cout << "------------------------- You called for Help! -------------------------" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|      How to use:                                                     |" << endl;
    cout << "|        -> ./engine (xml file)                                        |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|      XML File:                                                       |" << endl;
    cout << "|        -> A path to the xml file that contains the name of the       |" << endl;
    cout << "|           3d files.                                                  |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|      What you can do:                                                |" << endl;
    cout << "|        -> q or w: Rotate in the X axis.                              |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> e or r: Rotate in the Y axis.                              |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> t or y: Rotate in the Z axis.                              |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> z or x: Translate in the Z axis.                           |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> l: Activate line mode.                                     |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> f: Activate fill mode.                                     |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> p: Activate point mode.                                    |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> a: Reset the angle and axis.                               |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> i or k: Zoom out and Zoom in.                              |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> m or n: Move camera upwards and downwards.                 |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> o or u: Move camera right and left.                        |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> UP key or DOWN key: Translate in the Y axis.               |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> LEFT key or RIGHT key: Translate in the X axis.            |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> ESC: Close app.                                            |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "------------------------------- THE END --------------------------------" << endl;
}


int main(int argc, char** argv){
// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Projeto");

    #ifndef __APPLE__
        glewInit();
    #endif
    glEnableClientState(GL_VERTEX_ARRAY);

    int xml=0;

    if(argc < 2) {
        cout << "Invalid number of arguments." << endl;
        return 0;
    }

    else if(strcmp(argv[1], "help") == 0){
        showHelp();
        return 0;
    } 

    xml = parseXML(argv[1]);
    if(xml==0) {
        cout << "I don't recognize that input. Need help? Try './engine help' if you need help!" << endl;
        return 0;
    }

    estruturas = lookFiles(argv[1]);

    cout << "Drawing." << endl;

// Required callback registry
    glutIdleFunc(renderScene);
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();

    return 0;
}

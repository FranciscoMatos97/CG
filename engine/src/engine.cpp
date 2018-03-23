
#include "../../headers/engine.h"
#include <math.h>

vector<Point*> pontos;
float xr=0, yr=0, zr=0;
float angle=0;
float xt=0, yt=0, zt=0;
float cx=M_PI_4, cz=M_PI_4;
float r = 10.0;
//cz beta, cx alpha

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

    glBegin(GL_LINES);

    // draw line for x axis
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(5.0, 0.0, 0.0);
	// draw line for y axis
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 5.0, 0.0);
	// draw line for Z axis
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 5.0);

	glEnd();

	glBegin(GL_TRIANGLES);

    srand (time(NULL));
    int color=0;
    float a, b, c;

    for (vector<Point*>:: iterator i = pontos.begin(); i != pontos.end(); ++i, color++) {
        Point p = **i;

        if(color%3==0) {
            a = (float)rand() / (float)RAND_MAX;
            b = (float)rand() / (float)RAND_MAX;
            c = (float)rand() / (float)RAND_MAX;

            if(a<=0.1 && b<=0.1 && c<=0.1) a=1;

            glColor3f(a,b,c);
        }
        glVertex3f(p.getX(),p.getY(),p.getZ());
    }

    glEnd();

// End of frame
    glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {
    float inc=0.1;
// put code to process regular keys in here
    if(key == 27){
        exit(0);
    }
    //zoom in

    if(key == 'i'){
        r+=inc;
        glutPostRedisplay();
    }
    //zoom out
    if(key == 'k'){
        r-=inc;
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


    if(key == 'z'){
        zt++;
        glutPostRedisplay();
    }

    if(key == 'x'){
        zt--;
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
        r = 10;
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
// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

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

    vector<Struct*> list = lookupFiles(argv[1]);

    /*if (file_list.size()) {
        for (vector<string>::const_iterator i = file_list.begin(); i != file_list.end(); ++i) {
            vector<Point*> p = readFile(*i);
            for (vector<Point*>:: iterator it = p.begin(); it != p.end(); ++it) {
                Point pt = **it;
                pontos.push_back(new Point(pt.getX(), pt.getY(), pt.getZ()));
            }
        }
    }*/

    cout << "Drawing." << endl;

    glPolygonMode(GL_FRONT,GL_LINE);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();

    return 0;
}

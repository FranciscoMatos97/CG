
#include "headers/engine.h"

vector<Point*> pontos;
float xr=0, yr=0, zr=0;
float angle=0;
float xt=0, yt=0, zt=0;

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

    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

// put the geometric transformations here
    glRotatef(angle,xr,yr,zr);
    glTranslatef(xt,yt,zt);

// put drawing instructions here

    glBegin(GL_TRIANGLES);

    srand (time(NULL));
    int color=0;
    float a, b, c;

    for (vector<Point*>:: iterator i = pontos.begin(); i != pontos.end(); ++i, color++) {
        Point p = **i;

        if(color%3==0) {
            a = rand() % 2;
            b = rand() % 2;
            c = rand() % 2;

            if(a<=0.2 && b<=0.2 && c<=0.2) a=1;

            glColor3f(a,b,c);
        }
        glVertex3f(p.getX(),p.getY(),p.getZ());
    }

    glEnd();

// End of frame
    glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {

// put code to process regular keys in here
    if(key == 27){
        exit(0);
    }

    if(key == 'r'){
        angle++;
        yr++;
        glutPostRedisplay();
    }

    if(key == 'e'){
        angle--;
        yr--;
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

    if(argc < 2) {
        cout << "Invalid number of arguments." << endl;
        return 0;
    }

    int xml = parseXML(argv[1]);
    if(xml==0) return -1;

    vector<string> file_list = lookupFiles(argv[1]);

    if (file_list.size()) {
        for (vector<string>::const_iterator i = file_list.begin(); i != file_list.end(); ++i) {
            vector<Point*> p = readFile(*i);
            for (vector<Point*>:: iterator it = p.begin(); it != p.end(); ++it) {
                Point pt = **it;
                pontos.push_back(new Point(pt.getX(), pt.getY(), pt.getZ()));
            }
        }
    }

    cout << "Drawing." << endl;

    glPolygonMode(GL_FRONT,GL_LINE);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();

    return 0;
}

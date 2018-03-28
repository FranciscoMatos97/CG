#include "../../headers/engine.h"

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

void figuraPrimitiva(Struct s){
    vector<Transform*> vt = s.getRefit();
    const char* nameTransf;
    float angle, x, y, z;

    glPushMatrix();

    for (vector<Transform *>::const_iterator t = vt.begin(); t != vt.end(); t++) {
        nameTransf = (*t)->Transform::getName().c_str();


        if (strcmp(nameTransf,"rotate")) {
            angle = (*t)->Transform::getAngle();
        }
        x = (*t)->Transform::getPoint()->Point::getX();
        y = (*t)->Transform::getPoint()->Point::getY();
        z = (*t)->Transform::getPoint()->Point::getZ();
        if (!strcmp(nameTransf,"translate")){
            glTranslatef(x,y,z);
        }
        else if (!strcmp(nameTransf,"rotate")) {
            glRotatef(angle,x,y,z);
        }
        else if (!strcmp(nameTransf,"scale")) {
            glScalef(x,y,z);
        }
    }

    vector<Point*> vp;
    Point p;


    srand (time(NULL));
    int color=0;
    float a, b, c;

    glBegin(GL_TRIANGLES);
    vp=s.getPoints();
            for (vector<Point *>::const_iterator i = vp.begin(); i != vp.end(); ++i, color++) {
                p = **i;
                if (color % 3 == 0) {
                    a = (float) rand() / (float) RAND_MAX;
                    b = (float) rand() / (float) RAND_MAX;
                    c = (float) rand() / (float) RAND_MAX;

                    if (a <= 0.1 && b <= 0.1 && c <= 0.1) a = 1;

                    glColor3f(a, b, c);
                }
                glVertex3f(p.getX(), p.getY(), p.getZ());
            }


    glEnd();

    glPopMatrix();
}

//define a cor do planeta
//e retorna a velocidade de rotação à volta do objeto correspondente
float rotacao(const char* nameFile){
    float r=0;

    if(!strcmp(nameFile,"sol.3d")){
        glColor3f(0.8,0.2,0.0);
        return 0;
    }
    else if(!strcmp(nameFile,"mercurio.3d")){
        glColor3f(0.2f, 0.2f, 0.2f);
        return 10;
    }
    else if(!strcmp(nameFile,"venus.3d")){
        glColor3f(0.8,0.5,0.0);
        return 8;
    }
    else if(!strcmp(nameFile,"terra.3d")){
        glColor3f(0.0,0.0,0.9);
        return 6;
    }
    else if(!strcmp(nameFile,"lua.3d") || !strcmp(nameFile,"io.3d") || !strcmp(nameFile,"titan.3d") || !strcmp(nameFile,"triton.3d")) {
        glColor3f(0.5, 0.8, 0.8);
        return 20;
    }
    else if(!strcmp(nameFile,"europa.3d")){
        glColor3f(0.5, 0.8, 0.8);
        return 30;
    }
    else if(!strcmp(nameFile,"ganymede.3d")){
        glColor3f(0.5, 0.8, 0.8);
        return 35;
    }
    else if( !strcmp(nameFile,"callisto.3d")){
        glColor3f(0.5, 0.8, 0.8);
        return 40;
    }
    else if(!strcmp(nameFile,"marte.3d")) {
        glColor3f(1.0, 0.0, 0.0);
        return 4;
    }
    else if(!strcmp(nameFile,"asteroide.3d")){
        glColor3f(0.7,0.7,0.7);
        return 6;
    }
    else if(!strcmp(nameFile,"jupiter.3d")){
        glColor3f(0.8,0.5,0.2);
        return 1.5;
    }
    else if(!strcmp(nameFile,"saturno.3d")){
        glColor3f(0.8,0.6,0.4);
        return 1;
    }
    else if(!strcmp(nameFile,"urano.3d")){
        glColor3f(0.5,0.5,1.0);
        return 0.5;
    }
    else if(!strcmp(nameFile,"neptuno.3d")){
        glColor3f(0.2,0.2,1.0);
        return 0.2;
    }
    else if(!strcmp(nameFile,"plutao.3d")){
        glColor3f(0.7,0.7,0.7);
        return 0.1;
    }

    return r;
}

void sistemaSolar(Struct s){
    const char* nameFile = s.getFile().c_str();
    vector<Transform*> vt = s.getRefit();
    const char* nameTransf;
    float angle, x, y, z;
    float raio;
    bool lua3d = (!strcmp(nameFile,"lua.3d") || !strcmp(nameFile,"io.3d") || !strcmp(nameFile,"europa.3d") ||
                !strcmp(nameFile,"ganymede.3d") || !strcmp(nameFile,"callisto.3d") ||
                !strcmp(nameFile,"titan.3d") || !strcmp(nameFile,"triton.3d"));

    glPushMatrix();

    //desenhar orbita dos planetas e buscar o raio das orbitas das luas
    if(strcmp(nameFile,"sol.3d")!=0 || strcmp(nameFile,"asteroide.3d")!=0){
        for (vector<Transform *>::const_iterator t = vt.begin(); t != vt.end(); t++) {
            nameTransf = (*t)->Transform::getName().c_str();
            if (!strcmp(nameTransf,"translate")){
                raio = (*t)->Transform::getPoint()->Point::getX();
            }
        }

        if(!lua3d) {
            glColor3f(0.5,0.8,0.8);
            glBegin(GL_POINTS);
            for(int i=0;i<360;++i) {
                glVertex3f(raio * sin(i), 0, raio * cos(i));
            }
            glEnd();
        }
    }

    float time, re, gr;
    time=1;
    re = glutGet(GLUT_ELAPSED_TIME)/100.f;
    gr = (re*360) / (time * 1000);

    //definir a cor do planeta/sol/asteroide e fazer rotação à volta do objeto correspondente
    if(!lua3d) glRotatef(gr*rotacao(nameFile),0,1,0);

    int lua=0;
    //fazer translações/rotações/escalas dos eixos
    for (vector<Transform *>::const_iterator t = vt.begin(); t != vt.end(); ++t) {
        nameTransf = (*t)->Transform::getName().c_str();
        if (!strcmp(nameTransf,"rotate")) angle = (*t)->Transform::getAngle();
        x = (*t)->Transform::getPoint()->Point::getX();
        y = (*t)->Transform::getPoint()->Point::getY();
        z = (*t)->Transform::getPoint()->Point::getZ();

        if (!strcmp(nameTransf,"translate")){
            if(lua3d) {
                //rotação da lua à volta do sol
                if (lua == 0) {
                    if (!strcmp(nameFile, "lua.3d"))
                        glRotatef(gr * rotacao("terra.3d"), 0, 1, 0);
                    else if (!strcmp(nameFile, "io.3d") || !strcmp(nameFile, "europa.3d") ||
                             !strcmp(nameFile, "ganymede.3d") || !strcmp(nameFile, "callisto.3d"))
                        glRotatef(gr * rotacao("jupiter.3d"), 0, 1, 0);
                    else if (!strcmp(nameFile, "titan.3d"))
                        glRotatef(gr * rotacao("saturno.3d"), 0, 1, 0);
                    else if (!strcmp(nameFile, "triton.3d"))
                        glRotatef(gr * rotacao("neptuno.3d"), 0, 1, 0);
                }

                glTranslatef(x, y, z);
                lua++;

                if(lua==1 && !strcmp(nameFile, "titan.3d")) glRotatef(gr*6, 0, 1, 0);

                //desenhar orbita da luas à volta do planeta
                if ((lua == 1 && strcmp(nameFile, "titan.3d")) || (lua==2 && !strcmp(nameFile, "titan.3d"))) {
                    glColor3f(0.5, 0.8, 0.8);
                    glBegin(GL_POINTS);
                    for (int k = 0; k < 360; ++k) {
                        glVertex3f(raio * sin(k), 0, raio * cos(k));
                    }
                    glEnd();
                  
                    //cor e rotação da lua sobre o planeta
                    glRotatef(gr * rotacao(nameFile), 0, 1, 0);
                }

                //rotação da lua sobre si própria
                if((lua == 2 && strcmp(nameFile, "titan.3d")) || (lua==3 && !strcmp(nameFile, "titan.3d")))
                    glRotatef(gr*6,0,1,0);
            }
            else glTranslatef(x,y,z);
        }
        else if (!strcmp(nameTransf,"rotate")) {
            glRotatef(angle,x,y,z);
        }
        else if (!strcmp(nameTransf,"scale")) {
            glScalef(x,y,z);
        }
    }

    string h = s.getFile();
    vector<Point*> vp = s.getPoints();
    Point p;
    int r, alpha;
    srand(r);
    srand(alpha);

    //desenhar planeta e fazer rotação sobre si próprio
    if(!strcmp(nameFile,"asteroide.3d")){
        for(int j=0; j<50; j++) {
            r=(rand()%8)+100; //r entre 100 e 108
            alpha=rand()%360; //alpha entre 0 e 360

            glPushMatrix();
            glTranslatef(r * sin(alpha), r * cos(alpha), 0);
            glRotatef(gr*6, 0, 1, 0);
            glBegin(GL_TRIANGLES);
            for (vector<Point *>::iterator i = vp.begin(); i != vp.end(); i++) {
                p = **i;
                glVertex3f(p.getX(), p.getY(), p.getZ());
            }
            glEnd();
            glPopMatrix();
        }
    }
    else {
        glRotatef(gr*6, 0, 1, 0);

        glBegin(GL_TRIANGLES);
        for (vector<Point *>::iterator i = vp.begin(); i != vp.end(); i++) {
            p = **i;
            glVertex3f(p.getX(), p.getY(), p.getZ());
        }
        glEnd();

        //aneis de saturno
        if(!strcmp(nameFile,"saturno.3d")){
            glColor3f(0.8,0.6,0.0);
            glRotatef(-70,1,0,0);
            glutSolidTorus(10,14,2,100);
        }
    }

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

    const char* nf;
    for(vector<Struct>::const_iterator f = estruturas.begin(); f != estruturas.end(); f++) {
        Struct s = (*f);
        nf = s.getFile().c_str();
        if(!strcmp("plane.3d",nf) || !strcmp("box.3d",nf) || !strcmp("sphere.3d",nf) || !strcmp("cone.3d",nf))
            figuraPrimitiva(s);
        else sistemaSolar(s);
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
        r = 10;
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
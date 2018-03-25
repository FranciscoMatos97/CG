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
        angle = (*t)->Transform::getAngle();
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

    vector<Point*> vp = s.getPoints();
    Point p;
    srand (time(NULL));
    int color=0;
    float a, b, c;

    glBegin(GL_TRIANGLES);

    for (vector<Point*>::iterator i = vp.begin(); i != vp.end(); i++, color++) {
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
    else if(!strcmp(nameFile,"lua.3d")){
        glColor3f(0.5,0.8,0.8);
        return 4;
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
    int r, alpha;
    srand(r);
    srand(alpha);

    float time, re, gr;
    time=1;
    re = glutGet(GLUT_ELAPSED_TIME)/100.f;
    gr = (re*360) / (time * 1000);

    const char* nameFile = s.getFile().c_str();
    vector<Transform*> vt = s.getRefit();
    const char* nameTransf;
    float angle, x, y, z;
    float raio;

    glPushMatrix();

    //desenhar orbita
    if(strcmp(nameFile,"sol.3d")!=0 || strcmp(nameFile,"asteroide.3d")!=0){
        for (vector<Transform *>::const_iterator t = vt.begin(); t != vt.end(); t++) {
            nameTransf = (*t)->Transform::getName().c_str();
            if (!strcmp(nameTransf,"translate")){
                raio = (*t)->Transform::getPoint()->Point::getX();
            }
        }

        if(strcmp(nameFile,"lua.3d")!=0) {
            glColor3f(0.5,0.8,0.8);
            glBegin(GL_POINTS);
            for(int i=0;i<360;++i) {
                glVertex3f(raio * sin(i), 0, raio * cos(i));
            }
            glEnd();
        }
    }

    //definir a cor do planeta e fazer rotação à volta do objeto correspondente
    if(strcmp(nameFile,"lua.3d")!=0) glRotatef(gr*rotacao(nameFile),0,1,0);

    //fazer transação/rotação/escala dos eixos
    int lua=0;
    for (vector<Transform *>::const_iterator t = vt.begin(); t != vt.end(); t++) {
        nameTransf = (*t)->Transform::getName().c_str();
        angle = (*t)->Transform::getAngle();
        x = (*t)->Transform::getPoint()->Point::getX();
        y = (*t)->Transform::getPoint()->Point::getY();
        z = (*t)->Transform::getPoint()->Point::getZ();

        if (!strcmp(nameTransf,"translate")){
            if(!strcmp(nameFile,"lua.3d")) {
                if(lua==0) glRotatef(gr*6,0,1,0);
                glTranslatef(x,y,z);
                lua++;
                if(lua==1){
                    cout << s.getFile() << endl; //ao tirar isto daqui deixa de dar

                    //orbita
                    glColor3f(0.5,0.8,0.8);
                    glBegin(GL_POINTS);
                    for(int k=0;k<360;++k) {
                        glVertex3f(raio * sin(k), 0, raio * cos(k));
                    }
                    glEnd();

                    //cor e rotação
                    glRotatef(gr*rotacao(nameFile),0,1,0);
                }
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

    vector<Point*> vp = s.getPoints();
    Point p;

    //desenhar planeta e fazer rotação sobre si próprio
    if(!strcmp(nameFile,"asteroide.3d")){
        for(int j=0; j<100; j++) {
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
            glColor3f(0.8,0.8,0.8);
            glBegin(GL_POINTS);
            for(int j=0; j<5; j+=1){
                for(int i=0;i<360;++i) {
                    glVertex3f( j*(71/6) * sin(i),0,  j*(71/6) * cos(i));
                }
            }
            glEnd();
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

    Struct s;
    string nameFile;
    const char* nf;

    for(vector<Struct>::const_iterator f = estruturas.begin(); f != estruturas.end(); f++) {
        s = *f;
        nameFile = s.getFile();
        nf = nameFile.c_str();
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

    //estruturas = lookupFiles(argv[1]);
    /*SE AS ESTRUTURAS VIEREM SEM OS PONTOS FAZER:
    for(vector<Struct>::const_iterator f = estruturas.begin(); f != estruturas.end(); f++) {
        Struct s = *f;
        vector<Point*> vp = readFile(s.getFile());
        s.setPoints(vp);
    }*/







    //TESTE figuraPrimitiva
    /*vector<Transform*> tplane;
    Point* ppl = new Point(35,0,0);
    Transform* tpl = new Transform("translate",NULL,ppl);
    tplane.push_back(tpl);
    vector<Point*> pplane = readFile("plane.3d");
    Struct* plane = new Struct("plane.3d",tplane,pplane);

    estruturas.push_back(*plane);

    vector<Transform*> tbox;
    Point* scale = new Point(2,1,1);
    Point* trans = new Point(0,20,0);
    Transform* tt = new Transform("translate",NULL,trans);
    Transform* tsc = new Transform("scale",NULL,scale);
    tbox.push_back(tsc);
    tbox.push_back(tt);
    vector<Point*> pbox = readFile("box.3d");
    Struct* box = new Struct("box.3d",tbox,pbox);

    estruturas.push_back(*box);

    vector<Transform*> tsphere;
    Point* scaleS = new Point(5,5,5);
    Point* transS = new Point(2.5,0,0);
    Transform* ttS = new Transform("translate",NULL,transS);
    Transform* tscS = new Transform("scale",NULL,scaleS);
    tsphere.push_back(tscS);
    tsphere.push_back(ttS);
    vector<Point*> psphere = readFile("sphere.3d");
    Struct* sphere = new Struct("sphere.3d",tsphere,psphere);

    estruturas.push_back(*sphere);

    vector<Transform*> tcone;
    Point* pc = new Point(0,0,1);
    Transform* tc = new Transform("rotate",90,pc);
    tcone.push_back(tc);
    vector<Point*> pcone = readFile("cone.3d");
    Struct* cone = new Struct("cone.3d",tcone,pcone);

    estruturas.push_back(*cone);*/



    //TESTE sistemaSolar
    vector<Transform*> tsol;
    vector<Point*> psol = readFile("sol.3d");
    Struct* sol = new Struct("sol.3d",tsol,psol);

    estruturas.push_back(*sol);

    vector<Transform*> tmercurio;
    Point* pm = new Point(35,0,0);
    Transform* t1 = new Transform("translate",NULL,pm);
    tmercurio.push_back(t1);
    vector<Point*> pmercurio = readFile("mercurio.3d");
    Struct* mercurio = new Struct("mercurio.3d",tmercurio,pmercurio);

    estruturas.push_back(*mercurio);

    vector<Transform*> tvenus;
    Point* pv = new Point(66/1.5,0,0);
    Transform* tv = new Transform("translate",NULL,pv);
    tvenus.push_back(tv);
    vector<Point*> pvenus = readFile("venus.3d");
    Struct* venus = new Struct("venus.3d",tvenus,pvenus);

    estruturas.push_back(*venus);

    vector<Transform*> tterra;
    Point* pt = new Point(92/1.7654,0,0);
    Transform* t2 = new Transform("translate",NULL,pt);
    tterra.push_back(t2);
    vector<Point*> pterra = readFile("terra.3d");
    Struct* terra = new Struct("terra.3d",tterra,pterra);

    estruturas.push_back(*terra);

    vector<Transform*> tlua;
    Point* pl1 = new Point(52,0,0);
    Point* pl2 = new Point(6,0,0);
    Transform* t3 = new Transform("translate",0,pl1);
    Transform* t4 = new Transform("translate",0,pl2);
    tlua.push_back(t3);
    tlua.push_back(t4);
    vector<Point*> plua = readFile("lua.3d");
    Struct* lua = new Struct("lua.3d",tlua,plua);

    estruturas.push_back(*lua);

    vector<Transform*> tmarte;
    Point* pmr = new Point(70,0,0);
    Transform* tmr = new Transform("translate",NULL,pmr);
    tmarte.push_back(tmr);
    vector<Point*> pmarte = readFile("marte.3d");
    Struct* marte = new Struct("marte.3d",tmarte,pmarte);

    estruturas.push_back(*marte);

    vector<Transform*> tasteroide;
    Point* past = new Point(1,0,0);
    Transform* tast = new Transform("rotate",90,past);
    tasteroide.push_back(tast);
    vector<Point*> pasteroide = readFile("asteroide.3d");
    Struct* asteroide = new Struct("asteroide.3d",tasteroide,pasteroide);

    estruturas.push_back(*asteroide);

    vector<Transform*> tjupiter;
    Point* pj = new Point(478/3,0,0);
    Transform* tj = new Transform("translate",NULL,pj);
    tjupiter.push_back(tj);
    vector<Point*> pjupiter = readFile("jupiter.3d");
    Struct* jupiter = new Struct("jupiter.3d",tjupiter,pjupiter);

    estruturas.push_back(*jupiter);

    vector<Transform*> tsaturno;
    Point* ps = new Point(881/3,0,0);
    Transform* ts = new Transform("translate",NULL,ps);
    tsaturno.push_back(ts);
    vector<Point*> psaturno = readFile("saturno.3d");
    Struct* saturno = new Struct("saturno.3d",tsaturno,psaturno);

    estruturas.push_back(*saturno);

    vector<Transform*> turano;
    Point* pu = new Point(1769/5,0,0);
    Transform* tu = new Transform("translate",NULL,pu);
    turano.push_back(tu);
    vector<Point*> purano = readFile("urano.3d");
    Struct* urano = new Struct("urano.3d",turano,purano);

    estruturas.push_back(*urano);

    vector<Transform*> tneptuno;
    Point* pn = new Point(2769/6,0,0);
    Transform* tn = new Transform("translate",NULL,pn);
    tneptuno.push_back(tn);
    vector<Point*> pneptuno = readFile("neptuno.3d");
    Struct* neptuno = new Struct("neptuno.3d",tneptuno,pneptuno);

    estruturas.push_back(*neptuno);

    vector<Transform*> tplutao;
    Point* pp = new Point(3612/6,0,0);
    Transform* tp = new Transform("translate",NULL,pp);
    tplutao.push_back(tp);
    vector<Point*> pplutao = readFile("plutao.3d");
    Struct* plutao = new Struct("plutao.3d",tplutao,pplutao);

    estruturas.push_back(*plutao);







    cout << "Drawing." << endl;

// Required callback registry
    glutIdleFunc(renderScene);
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

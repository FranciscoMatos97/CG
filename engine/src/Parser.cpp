
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <stdlib.h>

#include "../../headers/tinyxml2.h"
#include "../../headers/Transform.h"
#include "../../headers/Struct.h"
#include "../../headers/Light.h"
#include "../../headers/Material.h"

using namespace std;
using namespace tinyxml2;

Struct s3;


Struct readFile(string file_name, Struct s){

    vector<Point*> points_list, normals_list, textures_list;
    vector<string> tokens;
    string buf;
    string line;
    int index = 0;
    bool readPoints = false, readNormals = false, readTextures = false;
    float x, y, z;

    string f = "../files/" + file_name;

    const char * f_n = f.c_str();
    ifstream file (f_n);

    if(file.is_open()){
        cout << "Processing " << file_name << endl;
        while(getline(file,line)) { // percorrer as linhas do ficheiro
            if(!strcmp(line.c_str(),"----Points----")) {
                getline(file,line);
                readPoints = true; readNormals = false, readTextures = false;
            }

            if(!strcmp(line.c_str(),"----Normals----")) {
                getline(file,line);
                readPoints = false; readNormals = true, readTextures = false;
            }

            if(!strcmp(line.c_str(),"----Textures----")) {
                getline(file,line);
                readPoints = false; readNormals = false, readTextures = true;
            }

            stringstream ss(line);
            while (ss >> buf) {
                tokens.push_back(buf); // percorrer as coordenadas dos pontos em cada linha
            }
            if(strcmp(line.c_str(),"--- New ---")) {
                x = atof(tokens.at(index).c_str());
                y = atof(tokens.at(index+1).c_str());
                z = atof(tokens.at(index+2).c_str());

                // adicionar ponto ao vector correspondente
                if(readPoints) points_list.push_back(new Point(x, y, z));
                if(readNormals) normals_list.push_back(new Point(x, y, z));
                if(readTextures) textures_list.push_back(new Point(x, y, z));
            }
            index += 3; // incrementar o índice para ler ponto seguinte
        }
        file.close();
    }
    else cout << "Error opening " << file_name << endl;

    s.setPoints(points_list);
    s.setNormals(normals_list);
    s.setTextures(textures_list);

    return s;

  /*  cout << "POINTS" << endl;
    for(int i=0; i<points_list.size();i++){
        cout << points_list.at(i)->getX() << " " << points_list.at(i)->getY() << " " << points_list.at(i)->getZ() << endl;
    }

    cout << "NORMALS" << endl;
    for(int i=0; i<normals_list.size();i++){
        cout << normals_list.at(i)->getX() << " " << normals_list.at(i)->getY() << " " <<normals_list.at(i)->getZ() << endl;
    }

    cout << "TEXTURES" << endl;
    for(int i=0; i<textures_list.size();i++){
        cout << textures_list.at(i)->getX() << " " << textures_list.at(i)->getY() << " " << textures_list.at(i)->getZ() << endl;
    }*/
}


Struct lookUpTranslate(XMLElement* element, Struct s){
    string transf;
    float timeT, x, y, z;
    vector<Point*> pl;

    transf = element->Name();
    if(element->Attribute("time")){
        timeT = atof( element->Attribute("time"));
    }
    else timeT = 0;

    if(element->Attribute("x")){
        x = atof(element->Attribute("x"));
    }
    else x = 0;

    if(element->Attribute("y")){
        y = atof(element->Attribute("y"));
    }
    else y = 0;

    if(element->Attribute("z")){
        z = atof(element->Attribute("z"));
    }
    else z = 0;

    if(x!=0 || y!=0 || z!=0) pl.push_back(new Point(x,y,z));

    for(element = element->FirstChildElement(); element; element=element->NextSiblingElement()){
        if(!strcmp(element->Name(), "point")) {
            x = atof(element->Attribute("x"));
            y = atof(element->Attribute("y"));
            z = atof(element->Attribute("z"));
        }

        pl.push_back(new Point(x,y,z));
    }

    Transform* t = new Transform(transf,timeT,0,pl);
    s.addTransform(t);

    return s;
}


Struct lookUpTransformation(XMLElement* element, Struct s){
    string transf;
    float timeT,angle,x,y,z;
    vector<Point*> pl;

    transf = element->Name();
    if(element->Attribute("angle")){
        angle = atof( element->Attribute("angle"));
    }
    else angle = 0;

    if(element->Attribute("time")){
        timeT = atof( element->Attribute("time"));
    }
    else timeT = 0;

    if(element->Attribute("x")){
        x = atof( element->Attribute("x"));
    }
    else x = 0;

    if(element->Attribute("y")){
        y = atof(element->Attribute("y"));
    }
    else y=0;

    if(element->Attribute("z")){
        z = atof(element->Attribute("z"));
    }
    else z=0;

    pl.push_back(new Point(x,y,z));
    Transform* t = new Transform(transf,timeT,angle,pl);

    s.addTransform(t);

    return s;
}


Struct lookUpLight(XMLElement* element, Struct s) {
    int isPoint=0;
    Point* point;

    vector<Light*> lights;

    for(element = element->FirstChildElement(); element; element=element->NextSiblingElement()){
        if(!strcmp(element->Name(), "light")) {
            if(!strcmp(element->Attribute("type"),"POINT")) isPoint=1;
            point->setX(atof(element->Attribute("x")));
            point->setY(atof(element->Attribute("y")));
            point->setZ(atof(element->Attribute("z")));

            lights.push_back(new Light(isPoint,point));
        }
        isPoint=0;
    }

    s.setLights(lights);

    return s;
}


Struct lookUpMaterial(XMLElement* element, Struct s) {
    Point* diffuse = new Point(0.0, 0.0, 0.0);
    Point* ambient = new Point(0.0, 0.0, 0.0);
    Point* diffuseANDambient = new Point(0.0, 0.0, 0.0);
    Point* specular = new Point(0.0, 0.0, 0.0);
    Point* emission = new Point(0.0, 0.0, 0.0);
    float shininess = 128.0;

    // Diffuse
    if(element->Attribute("diffuseX"))
            diffuse->setX(atof(element->Attribute("diffuseX")));
    if(element->Attribute("diffuseY"))
            diffuse->setY(atof(element->Attribute("diffuseY")));
    if(element->Attribute("diffuseZ"))
            diffuse->setZ(atof(element->Attribute("diffuseZ")));

    // Ambient
    if(element->Attribute("ambientX"))
            ambient->setX(atof(element->Attribute("ambientX")));
    if(element->Attribute("ambientY"))
            ambient->setY(atof(element->Attribute("ambientY")));
    if(element->Attribute("ambientZ"))
            ambient->setZ(atof(element->Attribute("ambientZ")));

    // Diffuse and Ambient
    if(element->Attribute("diffuseANDambientX"))
            diffuse->setX(atof(element->Attribute("diffuseANDambientX")));
    if(element->Attribute("diffuseANDambientY"))
            diffuse->setY(atof(element->Attribute("diffuseANDambientY")));
    if(element->Attribute("diffuseANDambientZ"))
            diffuse->setZ(atof(element->Attribute("diffuseANDambientZ")));

    // Specular
    if(element->Attribute("specularX"))
        specular->setX(atof(element->Attribute("specularX")));
    if(element->Attribute("specularY"))
        specular->setY(atof(element->Attribute("specularY")));
    if(element->Attribute("specularZ"))
        specular->setZ(atof(element->Attribute("specularZ")));

    // Emission
    if(element->Attribute("emissionX"))
        emission->setX(atof(element->Attribute("emissionX")));
    if(element->Attribute("emissionY"))
        emission->setY(atof(element->Attribute("emissionY")));
    if(element->Attribute("emissionZ"))
        emission->setZ(atof(element->Attribute("emissionZ")));

    // Shininess
    if(element->Attribute("shininess"))
        shininess = atof(element->Attribute("shininess"));

    Material* m = new Material(diffuse, ambient, diffuseANDambient, specular, emission, shininess);
    s.setMaterial(*m);

    return s;
}


Struct lookUpModel(XMLElement* elementAux, Struct s) {

    if(elementAux->Attribute("file")){
        string file3d = elementAux->Attribute("file");
        s.setFile3d(file3d);
        s = readFile(file3d,s);
        //s.fillBuffer();
    }

    if(elementAux->Attribute("texture")){
        string fileTexture = elementAux->Attribute("texture");
        s.setFileTexture(fileTexture);
        //prepareTexture
    }

    s = lookUpMaterial(elementAux,s);

    return s;
}


vector<Struct> lookAux(XMLElement* element){
    XMLElement* elementAux;
    string file;
    string transf;
    XMLElement* element3;
    vector<Struct> s;
    vector<Transform*> transforms;
    int c=0;
    vector<Transform*> vt;

    for(element=element->FirstChildElement(); element; element=element->NextSiblingElement()){
            if(!strcmp(element->Name(), "models")){
                c++;

                elementAux = element->FirstChildElement("model");
                for(; elementAux; elementAux=elementAux->NextSiblingElement()){
                    if(!strcmp(elementAux->Name(),"model")){
                        s3 = lookUpModel(elementAux,s3);
                        s.push_back(s3);
                        if(c==1){
                            vt = s3.getRefit();
                        }
                        s3 = *(new Struct());
                    }
                }
            }

            else if(!strcmp(element->Name(),"lights")){
                s3 = lookUpLight(element, s3);
            }

            else if(!strcmp(element->Name(),"rotate") || !strcmp(element->Name(),"scale") || !strcmp(element->Name(),"color")){
                s3 = lookUpTransformation(element, s3);
            }

            else if(!strcmp(element->Name(),"translate")){
                s3 = lookUpTranslate(element, s3);
            }

            else if(!strcmp(element->Name(),"group")){
                element3 = element;
                vector<Struct> sAux = lookAux(element3);
                for(vector<Struct>::iterator j = sAux.begin(); j != sAux.end(); ++j){
                    j->addTransform(vt);
                }
                s.insert(s.end(), sAux.begin(), sAux.end());
            }
        }

        return s;
}


vector<Struct> lookFiles(char* file_name){

    vector<Struct> list, final;
    XMLDocument doc;
    XMLElement* element; 

    XMLError error = doc.LoadFile(file_name);

    if(error == 0){
        cout << "XML files from " << file_name << ": " << endl;
    }

    else cout << "Could not load XML file: " << file_name << "." << endl;

    for(element = doc.FirstChildElement("scene")->FirstChildElement("group"); element; element=element->NextSiblingElement()){
        list = lookAux(element);
        final.insert(final.end(), list.begin(), list.end());
    }

    return final;
}


int parseXML(char* file_name){

    XMLDocument doc;
    XMLError error;

    error = doc.LoadFile(file_name);


    if(error != 0) {
        cout << "Error loading " << file_name << endl;
        return 0;
    }

    return 1;
}

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

using namespace std;
using namespace tinyxml2;

Struct s3;

vector<Point*> readFile(string file_name){

    vector<Point*> point_list;
    vector<string> tokens;
    string buf;
    string line;
    int index = 0;
    float x, y, z;

    string f = "../files3d/" + file_name;
    const char * f_n = f.c_str();
    ifstream file (f_n);

    if(file.is_open()){
        cout << "Processing " << file_name << endl;
        while(getline(file,line)) { // percorrer as linhas do ficheiro
            stringstream ss(line);
            while (ss >> buf) {
                tokens.push_back(buf); // percorrer as coordenadas dos pontos em cada linha
            }
            if((strcmp("---",tokens.at(index).c_str()))!=0) {
                x = atof(tokens.at(index).c_str());
                y = atof(tokens.at(index+1).c_str());
                z = atof(tokens.at(index+2).c_str());
                point_list.push_back(new Point(x, y, z)); // adicionar ponto ao vector
            }
            index += 3; // incrementar o índice para ler ponto seguinte
        }
        file.close();

    }
    else cout << "Error opening " << file_name << endl;

    return point_list;
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

    if(x!=0 && y!=0 && z!=0) pl.push_back(new Point(x,y,z));

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

Struct lookupT(XMLElement* element, Struct s){
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
                        file = elementAux->Attribute("file");
                        cout << "-> " << file << endl;
                        vector<Point*> vp = readFile(file);
                        s3.setPoints(vp);
                        s3.setFile(file);
                        s3.fillBuffer();
                        s.push_back(s3);
                        if(c==1){
                            vt = s3.getRefit();
                        }
                        s3.clear();
                    }
                }
            }

            else if(!strcmp(element->Name(),"rotate") || !strcmp(element->Name(),"scale") || !strcmp(element->Name(),"color")){
                s3 = lookupT(element, s3);
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

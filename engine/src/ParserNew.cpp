#include "../../headers/ParserNew.h"
#include <string>
#include <math.h>
#include <stdlib.h>

vector<Struct*> lookAux(XMLElement* element){
    XMLElement* elementAux;
    string file;
    string transf;
    float angle,x,y,z;
    XMLElement* element3;
    vector<Struct*> s;
    vector<Transform*> transforms;

    for(; element; element=element->NextSiblingElement()){

            if(!strcmp(element->Name(), "models")){

                elementAux = element->FirstChildElement("model");
                for(;elementAux;elementAux=elementAux->NextSiblingElement()){
                    if(!strcmp(elementAux->Name(),"model")){
                        file = elementAux->Attribute("file");
                        cout << "-> " << file << endl;
                        s.push_back(new Struct(file,transforms));

                        /*cout << (*(s.front())).Struct::getFile() << endl;
                        for(vector<Transform*>::const_iterator j = (*(s.front())).Struct::getRefit().begin(); j != (*(s.front())).Struct::getRefit().end(); ++j){
                            cout << (*j)->Transform::getName() << endl;
                            cout << "Angle: " << (*j)->Transform::getAngle() << endl;
                            cout << "X: " << (*j)->Transform::getX() << endl;
                            cout << "Y: " << (*j)->Transform::getY() << endl;
                            cout << "Z: " << (*j)->Transform::getZ() << endl;
                        } */    
                    }
                }
                transforms.clear();

            }

            if(!strcmp(element->Name(),"rotate")){
                transf = element->Name();
                if(element->Attribute("angle")){
                    angle = (float) atoi(element->Attribute("angle"));
                }
                else angle=NULL;
                if(element->Attribute("x")){
                    x = (float) atoi( element->Attribute("x"));
                }
                else x = NULL;
                if(element->Attribute("y")){
                    y = (float) atoi(element->Attribute("y"));
                }
                else y=NULL;
                if(element->Attribute("z")){
                    z = (float) atoi(element->Attribute("z"));
                }
                else z=NULL;

                transforms.push_back(new Transform(transf,angle,x,y,z)); 

                for(vector<Transform*>::const_iterator j = transforms.begin(); j != transforms.end(); ++j){
                            cout << (*j)->getName() << endl;
                            cout << "Angle: " << (*j)->getAngle() << endl;
                            cout << "X: " << (*j)->getX() << endl;
                            cout << "Y: " << (*j)->getY() << endl;
                            cout << "Z: " << (*j)->getZ() << endl;
                } 
            }

            if(!strcmp(element->Name(),"translate")){
                transf = element->Name();
                if(element->Attribute("x")){
                    x = (float) atoi( element->Attribute("x"));
                }
                else x = NULL;
                if(element->Attribute("y")){
                    y = (float) atoi(element->Attribute("y"));
                }
                else y=NULL;
                if(element->Attribute("z")){
                    z = (float) atoi(element->Attribute("z"));
                }
                else z=NULL;

                transforms.push_back(new Transform(transf,NULL,x,y,z)); 

                for(vector<Transform*>::const_iterator j = transforms.begin(); j != transforms.end(); ++j){
                            cout << (*j)->Transform::getName() << endl;
                            cout << "Angle: " << (*j)->Transform::getAngle() << endl;
                            cout << "X: " << (*j)->Transform::getX() << endl;
                            cout << "Y: " << (*j)->Transform::getY() << endl;
                            cout << "Z: " << (*j)->Transform::getZ() << endl;
                } 
            }

            if(!strcmp(element->Name(),"scale")){
                transf = element->Name();
                if(element->Attribute("x")){
                    x = (float) atoi((char*) element->Attribute("x"));
                }
                else x = NULL;
                if(element->Attribute("y")){
                    y = (float) atoi(element->Attribute("y"));
                }
                else y=NULL;
                if(element->Attribute("z")){
                    z = (float) atoi(element->Attribute("z"));
                }
                else z=NULL;

                transforms.push_back(new Transform(transf,NULL,x,y,z)); 
            }

            if(!strcmp(element->Name(),"group")){
                element3 = element->FirstChildElement();
                vector<Struct*> sAux = lookAux(element3);
                s.insert(s.end(), sAux.begin(), sAux.end());
                sAux.clear();
            }
        }

        return s;

}

vector<Struct*> lookupFiles(char* file_name){

    vector<Struct*> list;
    XMLDocument doc;
    XMLElement* element; 

    XMLError error = doc.LoadFile(file_name);

    if(error == 0){
        cout << "XML files from " << file_name << ": " << endl;
    }

    else cout << "Could not load XML file: " << file_name << "." << endl;

    element=doc.FirstChildElement("scene")->FirstChildElement("group")->FirstChildElement();

    list = lookAux(element);

    /*for (vector<Struct*>::const_iterator i = list.begin(); i != list.end(); ++i) {
        cout << (*i)->Struct::getFile() << endl;

        for(vector<Transform*>::const_iterator j = (*i)->Struct::getRefit().begin(); j != (*i)->Struct::getRefit().end(); ++j){
            cout << (*j)->Transform::getName() << endl;
            cout << "Angle: " << (*j)->Transform::getAngle() << endl;
            cout << "X: " << (*j)->Transform::getX() << endl;
            cout << "Y: " << (*j)->Transform::getY() << endl;
            cout << "Z: " << (*j)->Transform::getZ() << endl;
        }        
    }*/

    return list;
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
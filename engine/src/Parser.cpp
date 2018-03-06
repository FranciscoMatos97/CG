#include "../../headers/Parser.h"

vector<string> lookupFiles(char* file_name){

    vector<string> file_list;
    XMLDocument doc;
    XMLElement* element;
    XMLError error;
    string file;

    error = doc.LoadFile(file_name);

    if(error == 0){
        cout << "XML files from " << file_name << ": " << endl;

        element = doc.FirstChildElement("scene")->FirstChildElement("model");
        for(;element;element=element->NextSiblingElement()){
            if(!strcmp(element->Name(),"model")){
                file = element->Attribute("file");
                file_list.push_back(file);
                cout << "-> " << file << endl;
            }
        }
    }
    else cout << "Could not load XML file: " << file_name << "." << endl;

    return file_list;
}

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
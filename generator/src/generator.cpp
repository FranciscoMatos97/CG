#include <iostream>
#include <stdio.h>
#include <istream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstring>
#include "../../headers/vertex.h"
#include "../../headers/Patch.h"
#include "string.h"

using namespace std;


void saveFile(vector<Point*> v, string filename){

    ofstream file;

    string f = "../files3d/" + filename; 

    file.open(f.c_str(), ios_base::app);

        for(int i=0; i<v.size(); ++i){
            file << v[i]->Point::getX() << ' ';
            file << v[i]->Point::getY() << ' ';
            file << v[i]->Point::getZ() << endl;
        }

        file << "--- New ---" << endl;

        file.close();

}

void showHelp(){
    cout << "------------------------- You called for Help! -------------------------" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|      How to use:                                                     |" << endl;
    cout << "|        -> ./generator (figure) (dimensions) (file)                   |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|      Supported figures:                                              |" << endl;
    cout << "|        -> plane:                                                     |" << endl;
    cout << "|              . Dimensions:                                           |" << endl;
    cout << "|                -> Size;                                              |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|              . Description:                                          |" << endl;
    cout << "|                -> Creates a square plane with the given size in the  |" << endl;
    cout << "|                   XZ plane.                                          |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> box:                                                       |" << endl;
    cout << "|              . Dimensions:                                           |" << endl;
    cout << "|                -> (X Size) (Y Size) (Z Size) (Divisions)             |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|              . Description:                                          |" << endl;
    cout << "|                -> Creates a box with the given sizes and number of   |" << endl;
    cout << "|                    divisions.                                        |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> sphere:                                                    |" << endl;
    cout << "|              . Dimensions:                                           |" << endl;
    cout << "|                -> (Radius) (Slices) (Stacks)                         |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|              . Description:                                          |" << endl;
    cout << "|                -> Creates a sphere with the given radius centered    |" << endl;
    cout << "|                   in the origin, with the slices and stacks          |" << endl;
    cout << "|                   specified.                                         |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|        -> cone:                                                      |" << endl;
    cout << "|              . Dimensions:                                           |" << endl;
    cout << "|                -> (Radius) (Height) (Slices) (Stacks)                |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|              . Description:                                          |" << endl;
    cout << "|                -> Creates a cone with the given radius and height    |" << endl;
    cout << "|                   centered in the origin, with the slices and        |" << endl;
    cout << "|                   stacks specified.                                  |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|      File:                                                           |" << endl;
    cout << "|        -> This is the output file in which you want to save the      |" << endl;
    cout << "|           generated coordinates.                                     |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "|      EXAMPLE USAGE:                                                  |" << endl;
    cout << "|        -> ./generator sphere 2 20 20 sphere.3d                       |" << endl;
    cout << "|                                                                      |" << endl;
    cout << "------------------------------- THE END --------------------------------" << endl;
}

string getPointsOfLine(string inputFile, int ctrl){
    int i;
    string ctrLine;
    ifstream file;
    file.open(inputFile.c_str());
    if(file.is_open()){
        for(i=0; i<ctrl; i++) getline(file,ctrLine);
        file.close();
    }
    return ctrLine;
}

vector<Point*> makePatch(int tesselation, string inputFile){
    vector<Patch*> patchList;
    int i, j, k, ind, patches, pos, ctrl;
    float number;
    string l, ctrLine;

    ifstream file;
    file.open(inputFile.c_str());

    if(file.is_open()){
        
        getline(file,l);

        patches = atoi(l.c_str());
        
        for(i=0; i<patches; i++){

            getline(file,l);
            vector<Point*> v;
            Patch* pat = new Patch();

            for(j=0; j<16; j++){
                
                pos = l.find(", ");
                ind = atoi(l.substr(0, pos).c_str());
                l.erase(0, pos+2);
                ctrl = 3 + patches + ind;
                ctrLine = getPointsOfLine(inputFile,ctrl);
                Point* p = new Point();
                for(k=0; k<3; k++){
                    pos = ctrLine.find(", ");
                    number = atof(ctrLine.substr(0, pos).c_str());
                    ctrLine.erase(0, pos+2);
                    if(k==0){
                        p->setX(number);  
                    }
                    if(k==1){
                        p->setY(number);
                    }
                    if(k==2){
                        p->setZ(number);
                    }
                }
                v.push_back(p);
            }
            pat->setCtrlPoints(v);
            patchList.push_back(pat);
        }
        Vertex* vx = new Vertex();
        vector<Point*> points = vx->bezierPatchTriangles(tesselation,patchList);
        return points;
    }


}

int main(int argc, char** argv){

    if(argc < 2){
        cout << "Not enough arguments" << endl;
        return 0;
    }

    float size=0;
    Vertex* vx = new Vertex();


    if(!strcmp(argv[1], "plane")){
        size = atoi(argv[2]);
        vx->makePlane(size);
        saveFile(vx->getPointsList(), argv[3]);
    }

    else if(!strcmp(argv[1], "box") && argc == 7){
        float x = atoi(argv[2]);
        float y = atoi(argv[3]);
        float z = atoi(argv[4]);
        int divisions = atoi(argv[5]);
        vx->makeBox(x, y, z, divisions);
        saveFile(vx->getPointsList(), argv[6]);
    }

    else if(!strcmp(argv[1], "sphere") && argc == 6){
        float radius = atoi(argv[2]);
        int slices = atoi(argv[3]);
        int stacks = atoi(argv[4]);
        vx->makeSphere(radius, slices, stacks);
        saveFile(vx->getPointsList(), argv[5]);
    }

    else if(!strcmp(argv[1], "cone") && argc == 7){
        float radius = atoi(argv[2]);
        float height = atoi(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);
        vx->makeCone(radius, height, slices, stacks);
        saveFile(vx->getPointsList(), argv[6]);
    }

    else if(!strcmp(argv[1], "torus") && argc == 7){
        float intRadius = atoi(argv[2]);
        float extRadius = atoi(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);
        vx->makeTorus(intRadius, extRadius, slices, stacks);
        saveFile(vx->getPointsList(), argv[6]);
    }

    else if(!strcmp(argv[1], "patches")){
        string nameFile = argv[2];
        int tess = atoi(argv[3]);
        string outFile = argv[4];
        vector<Point*> list = makePatch(tess,nameFile);
        saveFile(list,outFile);
    }

    else if(strcmp(argv[1], "help") == 0){
        showHelp();
        return 0;
    }

    else{
        cout << "I don't recognize that input. Need help? Try './generator help' if you need help!" << endl;
        return 0;
    }

    return 0;
}



#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstring>
#include "../../headers/vertex.h"
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

int main(int argc, char** argv){

    vector<Point*> v;

    float size=0;

    if(argc < 2){
        cout << "Not enough arguments" << endl;
        return 0;
    }


    if(strcmp(argv[1], "plane") == 0){
        size = atoi(argv[2]);
        v = makePlane(size);
        saveFile(v, argv[3]);
    }

    else if(strcmp(argv[1], "box") == 0 && argc == 7){
        float x = atoi(argv[2]);
        float y = atoi(argv[3]);
        float z = atoi(argv[4]);
        int divisions = atoi(argv[5]);
        v = makeBox(x, y, z, divisions);
        saveFile(v, argv[6]);
    }

    else if(strcmp(argv[1], "sphere") == 0 && argc == 6){
        float radius = atoi(argv[2]);
        int slices = atoi(argv[3]);
        int stacks = atoi(argv[4]);
        v = makeSphere(radius, slices, stacks);
        saveFile(v, argv[5]);
    }

    else if(strcmp(argv[1], "cone") == 0 && argc == 7){
        float radius = atoi(argv[2]);
        float height = atoi(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);
        v = makeCone(radius, height, slices, stacks);
        saveFile(v, argv[6]);
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



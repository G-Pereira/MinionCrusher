//
// Created by gpereira on 11/27/18.
//

#include <fstream>
#include "Blueprint.h"

Blueprint::Blueprint(string configFile) {
    ifstream f(configFile.c_str());
    if (f){

    } else{
        cerr << "Map blueprint file not found";
        exit(-1);
    }
}

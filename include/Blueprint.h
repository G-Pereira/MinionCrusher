#ifndef MINIONCRUSHER_BLUEPRINT_H
#define MINIONCRUSHER_BLUEPRINT_H

#include <iostream>
#include <vector>
#include "Base.h"
#include "PathTile.h"

class Blueprint {
public:
    Blueprint(std::string blueprintFile = "resources/blueprints/simple.blueprint");

    std::string blueprintFile;
};


#endif //MINIONCRUSHER_BLUEPRINT_H

#ifndef MINIONCRUSHER_BLUEPRINT_H
#define MINIONCRUSHER_BLUEPRINT_H

#include <iostream>
#include <vector>
#include "Base.h"
#include "PathTile.h"
#include "Battlefield.h"

class Blueprint {
public:
    Blueprint(std::string configFile = "resources/blueprints/simple.blueprint");

    void loadBlueprint(Battlefield *map);

private:
    std::string configFile;
};


#endif //MINIONCRUSHER_BLUEPRINT_H

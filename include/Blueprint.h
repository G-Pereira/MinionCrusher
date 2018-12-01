#ifndef MINIONCRUSHER_BLUEPRINT_H
#define MINIONCRUSHER_BLUEPRINT_H

#include <iostream>
#include <vector>
#include "Base.h"
#include "PathTile.h"

class Blueprint {
public:
    Blueprint(std::string configFile = "configs/simple.blueprint");

    void loadBlueprint(std::vector<std::vector<MapObject>> *map);

private:
    std::string configFile;
};


#endif //MINIONCRUSHER_BLUEPRINT_H

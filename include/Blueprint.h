#ifndef MINIONCRUSHER_BLUEPRINT_H
#define MINIONCRUSHER_BLUEPRINT_H

#include <iostream>
#include <vector>
#include "Base.h"
#include "PathTile.h"

class Blueprint {
public:

    /**
     * \brief A blueprint of the initial map of the game that a user plays on.
     *
     * @param blueprintFile Location of the blueprint file.
     */
    Blueprint(std::string blueprintFile = "resources/blueprints/simple.blueprint");

    std::string blueprintFile;
};


#endif //MINIONCRUSHER_BLUEPRINT_H


#include <Battlefield.h>

#include "Battlefield.h"

Battlefield::Battlefield(Blueprint *blueprint) {
    try {
        blueprint->loadBlueprint(this);
    }
    catch (std::exception const &e) {
        std::cerr << e.what();
    }
}

Battlefield::~Battlefield() {
    delete this->base;
}

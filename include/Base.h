/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */
#ifndef MINIONCRUSHER_BASE_H
#define MINIONCRUSHER_BASE_H

#include <inttypes.h>
#include "MapObject.h"

class Base : public MapObject {
public:
    Base(float x, float y, float width, float height, float health);
    virtual ~Base();
private:
    float health; // Health of the base the minions attack
    void setHealth(float health);
    const float& getHealth() const;
};


#endif //MINIONCRUSHER_BASE_H

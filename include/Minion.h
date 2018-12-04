/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#ifndef MINIONCRUSHER_MINION_H
#define MINIONCRUSHER_MINION_H

#include "MapObject.h"

class Minion : public MapObject {
public:
    Minion(float x, float y, float width, float height, float health, float damage, float speed);

    virtual ~Minion();


    void setHealth(float health);

    const float &getHealth() const;

    void setSpeed(float speed);

    const float &getSpeed() const;

    void setDamage(float damage);

    const float &getDamage() const;

    int moveCount = 0;

private:
    float health; // Health of the minion
    float damage; // The damage a minion does when attacking the base
    float speed; // The speed of a minion in distance/tick
};


#endif //MINIONCRUSHER_MINION_H

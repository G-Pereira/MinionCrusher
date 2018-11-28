/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#ifndef MINIONCRUSHER_TOWER_H
#define MINIONCRUSHER_TOWER_H

#include "MapObject.h"

class Tower : public MapObject {
public:
    Tower(float x, float y, float width, float height, float health, float speed, float damage, AmmoType ammo);
    virtual ~Tower();

    // Getters and setters below
    const float& getHealth() const;
    void setHealth(float health);

    const float& getSpeed() const;
    void setSpeed(float speed);

    const float& getDamage() const;
    void setDamage(float damage);

    const AmmoType &getAmmo() const;
    void setAmmo(AmmoType ammo);

private:
    float health;
    float speed;
    float damage;
    AmmoType ammo;
};


#endif //MINIONCRUSHER_TOWER_H

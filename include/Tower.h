/*
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#ifndef MINIONCRUSHER_TOWER_H
#define MINIONCRUSHER_TOWER_H

#include "MapObject.h"

class Tower : public MapObject {
public:
    Tower(float x, float y, float width, float height, float firePeriod, float range, float damage, AmmoType ammo);

    virtual ~Tower();

    // Getters and setters below

    const float &getFirePeriod() const;

    void setFirePeriod(float firePeriod);

    const float &getDamage() const;

    void setDamage(float damage);

    const AmmoType &getAmmo() const;

    void setAmmo(AmmoType ammo);

private:
    float firePeriod;
	float range;
    float damage;
	float rangeSquared;
    AmmoType ammo;
};


#endif //MINIONCRUSHER_TOWER_H

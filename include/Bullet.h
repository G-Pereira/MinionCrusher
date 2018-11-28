/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#ifndef MINIONCRUSHER_BULLET_H
#define MINIONCRUSHER_BULLET_H

#include "MapObject.h"

class Bullet : public MapObject {
public:
    Bullet(float x, float y, float width, float height, AmmoType ammo);
    virtual ~Bullet();

    const AmmoType &getAmmo() const;
    void setAmmo(AmmoType ammo);
private:
    AmmoType ammo;
};


#endif //MINIONCRUSHER_BULLET_H

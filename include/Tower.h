/*
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#ifndef MINIONCRUSHER_TOWER_H
#define MINIONCRUSHER_TOWER_H

#include <list>
#include "MapObject.h"
#include "Minion.h"

class Tower : public MapObject {
public:
    Tower(float x, float y, float width, float height, int firePeriod, float range, AmmoType ammo, ObjectType type);

    virtual ~Tower();

    uint8_t update(std::list<Minion> &minions);	/// Update function for a tower. Shoots if possible, elsewise it will load until shooting is available.

    // Getters and setters below

    const int &getFirePeriod() const;        /// Get the time between two shots

    void setFirePeriod(int inpFirePeriod);      /// Set the time between two shots

    const float &getDamage() const;          /// Get the damage the tower does to minions

    void setDamage(float inpDamage);            /// Set the damage the tower does to minions

    const AmmoType &getAmmo() const;         /// Get the ammotype the tower shoots with (not implemented)

    void setAmmo(AmmoType inpAmmo);          /// Set the ammotype the tower shoots with (not implemented)

    const float &getRange() const;           /// Get the maximum distance the tower can still shoot

    void setRange(float inpRange);           /// Set the maximum distance the tower can still shoot

    const int &getTicks() const;             /// Get the amount of ticks since the last shot of the tower

    void setTicks(int inpTicks);                /// Set the amount of ticks since the last shot of the tower

	void postRender() override;

private:
    int ticks = 0;
    int firePeriod;		// Period between two shots of a tower
    float range;		// Max distance a tower can shoot at
    float damage;		// Amount of health subtracted from a minion when hit by this tower
    AmmoType ammo;		// Type of ammo the tower shoots
	SDL_Rect target;	// Last object that has been fired at
};


#endif //MINIONCRUSHER_TOWER_H

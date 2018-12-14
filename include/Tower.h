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
    Tower(float x, float y, float width, float height, int firePeriod, float range, float damage, AmmoType ammo);

    virtual ~Tower();

	void update(std::list<Minion> &minions);

    // Getters and setters below

    const int &getFirePeriod() const;		/// Get the time between two shots

    void setFirePeriod(int firePeriod);		/// Set the time between two shots

    const float &getDamage() const;			/// Get the damage the tower does to minions

    void setDamage(float damage);			/// Set the damage the tower does to minions

    const AmmoType &getAmmo() const;		/// Get the ammotype the tower shoots with (not implemented)

    void setAmmo(AmmoType ammo);			/// Set the ammotype the tower shoots with (not implemented)

    const float &getRange() const;			/// Get the maximum distance the tower can still shoot

    void setRange(float range);				/// Set the maximum distance the tower can still shoot			

	const int &getTicks() const;			/// Get the amount of ticks since the last shot of the tower

	void setTicks(int ticks);				/// Set the amount of ticks since the last shot of the tower

private:
	int ticks = 0;
	int firePeriod;
	float range;
    float damage;
	float rangeSquared;	
    AmmoType ammo;
};


#endif //MINIONCRUSHER_TOWER_H

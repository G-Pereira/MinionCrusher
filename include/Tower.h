#ifndef MINIONCRUSHER_TOWER_H
#define MINIONCRUSHER_TOWER_H

#include <list>
#include "MapObject.h"
#include "Minion.h"

class Tower : public MapObject {
public:
    /**
     * Creates a Tower
     * @param x Tower position X coordinate
     * @param y Tower position Y coordinate
     * @param width Tower width
     * @param height Tower height
     * @param firePeriod Minimum time interval between two fires
     * @param range Maximum Tower range of fire
     * @param ammo Tower Ammo
     * @param type Type of Object to spawn in the Map
     */
    Tower(float x, float y, float width, float height, int firePeriod, float range, Ammo ammo, ObjectType type);

    virtual ~Tower();

    /**
     * Check if there are minions in the Tower range and whether it should fire or not
     * @param minions List of Minion to poll
     * @return In case of Minion death it returns the reward the player should get for the specific type of Minion that died otherwise returns zero
     */
    int update(std::list<Minion> &minions);

	/**
     * Get the time between two shots
     * @return Time interval between two shots
     */
    const int &getFirePeriod() const;        /// Get the time between two shots

	/**
     * Set the time between two shots
     * @param: inpFirePeriod time interval
     */
    void setFirePeriod(int inpFirePeriod);

	/**
   * Get the damage the tower does to minions
   */
    const float &getDamage() const;

    /**
     * Get the Ammo the tower shoots with (feature not implemented)
     * @return Tower's Ammo
     */
    const Ammo &getAmmo() const;

    /**
     * Set the ammotype the tower shoots with (feature not implemented)
     * @param inpAmmo Tower's Ammo
     */
    void setAmmo(Ammo inpAmmo);

    /**
     * Get the maximum distance the tower can still shoot
     * @return Tower's Range
     */
    const float &getRange() const;

    /**
     * Set the maximum distance the tower can still shoot
     * @param inpRange Tower' range
     */
    void setRange(float inpRange);

    /**
     * Get the amount of ticks since the last shot of the tower
     * @return Ticks since last shot
     */
    const int &getTicks() const;

    /**
     * Set the amount of ticks since the last shot of the tower
     * @param inpTicks Ticks since last shot
     */
    void setTicks(int inpTicks);

    /**
     * Render Tower's visual features like the fire animation
     */
	void postRender() override;

private:
    int ticks = 0;      /** Time since last fire */
    int firePeriod;		/** Period between two shots of a tower */
    float range;		/** Max distance a tower can shoot at */
    float damage;		/** Amount of health subtracted from a minion when hit by this tower */
    Ammo ammo;		    /** Type of ammo the tower shoots */
	SDL_Rect target;	/** Last object that has been fired at */
};


#endif //MINIONCRUSHER_TOWER_H

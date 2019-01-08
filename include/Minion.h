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
    Minion(float x, float y, float width, float height, float health, float damage, float speed, int bounty);

    virtual ~Minion();


    void setHealth(float health);        /// Set the health of the minion

    const float &getHealth() const;        /// Get the health of the minion

    const float &getMaxHealth() const;    /// Get the maximum health of the minion (health it starts with)

    void setSpeed(float speed);            /// Set the movement speed of the minion

    const float &getSpeed() const;        /// Get the movement speed of the minion

    void setDamage(float damage);        /// Set the damage the minion does to the base when it hits the base.

    const float &getDamage() const;        /// Get the damage the minion does to the base when it hits the base.

    float traversedDistance = 0;                /// Counter that holds the distance traversed by a minion.

    bool operator==(const Minion &rhs) const;    /// Operator that checks if two minions are the same

    bool operator!=(const Minion &rhs) const;    /// Operator that checks if two minions are the different

    void postRender() override;		/// show the health bar of the minion

	int bounty; // Money awarded to player when this minion is killed

	const ObjectType objectType = (ObjectType) 9;

protected:
    float health; // Health of the minion
    float max_health; // max health of the minion
    float damage; // The damage a minion does when attacking the base
    float speed; // The speed of a minion in distance/tick
};


#endif //MINIONCRUSHER_MINION_H

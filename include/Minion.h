#ifndef MINIONCRUSHER_MINION_H
#define MINIONCRUSHER_MINION_H

#include "MapObject.h"

class Minion : public MapObject {
public:
    Minion(float x, float y, float width, float height, float health, float damage, float speed, int bounty,
           ObjectType type);

    virtual ~Minion();


    void setHealth(float health);                /// Set the health of the minion

    const float &getHealth() const;                /// Get the health of the minion

    const float &getMaxHealth() const;            /// Get the maximum health of the minion (health it starts with)

    void setDamage(float inpDamage);            /// Set the damage the minion does to the base when it hits the base.

    const float &getDamage() const;                /// Get the damage the minion does to the base when it hits the base.

    float traversedDistance = 0;                /// Counter that holds the distance traversed by a minion.

    bool operator==(const Minion &rhs) const;   /// Operator that checks if two minions are the same

    bool operator!=(const Minion &rhs) const;   /// Operator that checks if two minions are the different

    void postRender() override;                    /// show the health bar of the minion


    const ObjectType objectType = (ObjectType) 9;
    float maxSpeed;    // Maximum speed the minion has when not frozen
    float speed;    // The speed of a minion in distance/tick
    int bounty;        // Money awarded to player when this minion is killed

protected:
    float health; // Health of the minion
    float max_health; // max health of the minion
    float damage; // The damage a minion does when attacking the base
};


#endif //MINIONCRUSHER_MINION_H

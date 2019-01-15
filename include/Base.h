#ifndef MINIONCRUSHER_BASE_H
#define MINIONCRUSHER_BASE_H

#include <inttypes.h>
#include "MapObject.h"

/**
 * Entity that the player is meant to defend
 */
class Base : public MapObject {
public:
    /**
     * Base model with represents the entity the player has to defend
     * @param x X coordinate
     * @param y Y coordinate
     * @param width Base's width
     * @param height Base's height
     * @param health Base's health
     */
    Base(float x, float y, float width, float height, float health);

    virtual ~Base();

    /**
     * Damage the base by a determined amount
     * @param damage Damage to be dealt
     */
    void doDamage(float damage);

    /**
     * Renders Base's animations and status
     */
    void postRender() override;

    /**
     * Gets Base's remaining health
     * @return Remaining health
     */
    const float &getHealth() const;

    /**
     * Identify what type of object a Base is. Used to render the correct entity in the Map
     */
    const ObjectType objectType = (ObjectType) 5;

private:
    /**
     * Health of the base the minions attack
     */
    float health;

    /**
     * Health of the minion
     */
    float max_health;

    /**
     * Set Base's remaining health
     * @param inputHealth Remaining health
     */
    void setHealth(float inputHealth);
};


#endif //MINIONCRUSHER_BASE_H

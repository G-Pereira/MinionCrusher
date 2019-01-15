#ifndef MINIONCRUSHER_BASE_H
#define MINIONCRUSHER_BASE_H

#include <inttypes.h>
#include "MapObject.h"

class Base : public MapObject {
public:
    /**
     * \brief Base model with represents the entity the player has to defend
     * The Object is created at
     * @param x X coordinate
     * @param y Y coordinate
     */
    Base(float x, float y, float width, float height, float health);

    virtual ~Base();

    /**
     * Damage the base by a determined amount
     * @param Damage Damage to be dealt
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
    float health; /// Health of the base the minions attack
	float max_health; /// Health of the minion

	/**
	 * Set Base's remaining health
	 * @param inputHealth Remaining health
	 */
    void setHealth(float inputHealth);
};


#endif //MINIONCRUSHER_BASE_H

/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */
#ifndef MINIONCRUSHER_BASE_H
#define MINIONCRUSHER_BASE_H

#pragma warning( push )
#include <inttypes.h>
#pragma warning( pop )
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

    void doDamage(float damage);    /// Damage the base by a determined amount

	void postRender() override;

	const float &getHealth() const;

private:
    float health; // Health of the base the minions attack
	float max_health; // Health of the minion
    void setHealth(float inputHealth);
};


#endif //MINIONCRUSHER_BASE_H

/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#ifndef MINIONCRUSHER_MAPOBJECT_H
#define MINIONCRUSHER_MAPOBJECT_H

#include "types.h"
#ifdef _WIN32
#include <SDL.h>
#else
#include "SDL2/SDL.h"
#endif

/**
 * In the Minioncrusher, any object that is drawn on the map is a MapObject. These objects are easily recognized
 * as they have a position on the map. The coordinates are currently defined as floats.
 */
class MapObject {
public:
    /**
     * The object is constructed with both X and Y coordinates as every object must have an initial position. Dimensions
     * are fixed.
     * @param x X coordinate
     * @param y Y coordinate
     */
    MapObject(float x, float y, float width, float height);

    /**
     * Overloaded constructor if one gives an object of type CartesianCoordinates as parameter. Dimensions are fixed.
     */
    MapObject(CartesianCoordinates coordinates, ObjectSize dimensions);

    /**
     * Empty destructor.
     */
    virtual ~MapObject();

    // Below here there are only getters and setters

    /**
     * Get a constant reference to the cartesian coordinates of this MapObject.
     * @return CartesianCoordinates&
     */
    const CartesianCoordinates &getCoordinates() const;

    /**
     * Set the coordinates.
     * @param coordinates
     */
    void setCoordinates(CartesianCoordinates coordinates);

    /**
     * Overloading setter to set the coordinates.
     * @param x X position
     * @param y Y position
     */
    void setCoordinates(float x, float y);

    /**
     * Get a reference to the dimensions of this object.
     * @return ObjectSize&
     */
    const ObjectSize &getDimensions() const;

	/**
	 * Get a reference to the dimensions of this object.
	 * @return ObjectSize&
	 */
	const SDL_Texture * getTexture() const;

private:
    CartesianCoordinates coordinates; // Position on the map
    const ObjectSize dimensions;  // Dimensions on the map
	SDL_Texture * texture;
};


#endif //MINIONCRUSHER_MAPOBJECT_H

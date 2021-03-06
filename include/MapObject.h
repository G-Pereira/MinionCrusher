#ifndef MINIONCRUSHER_MAPOBJECT_H
#define MINIONCRUSHER_MAPOBJECT_H

#include "types.h"
#include "RenderElement.h"


/**
 * In Minioncrusher, any object that is drawn on the map is a MapObject. These objects are easily recognized
 * as they have a position on the map. The coordinates are currently defined as floats.
 */
class MapObject : public RenderElement {
public:
    /**
     * The object is constructed with both X and Y coordinates as every object must have an initial position. Dimensions
     * are fixed.
     * @param x X coordinate
     * @param y Y coordinate
     */
    MapObject(float x, float y, float width, float height, ObjectType type);

    /**
     * Overloaded constructor if one gives an object of type CartesianCoordinates as parameter. Dimensions are fixed.
     */
    MapObject(CartesianCoordinates coordinates, ObjectSize dimensions, SDL_Texture *texture, ObjectType type);

    /**
     * Empty destructor.
     */
    virtual ~MapObject();

    // Below here there are only getters and setters

    /**
     * Get a constant reference to the cartesian coordinates of this MapObject.
     * @return CartesianCoordinates&
     */
    CartesianCoordinates getCoordinates();

    /**
     * Set the coordinates.
     * @param coordinates
     */
    void setCoordinates(CartesianCoordinates inputCoordinates);

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
     * Set the dimensions of this object;
     * @param size
     */
    void setDimensions(ObjectSize size);

    /**
     * update the quad to match the current position and size.
     * @param tilewidth the width of tiles in pixels
     * @param tileheight the height of tiles in pixels
     */
    void updateQuad(float tilewidth, float tileheight);

    /**
    * Render this object using this renderer
    * @param renderer renderer to render with
    */
    void render() override;

    /**
     * Holds information if the object needs to be updated
     */
    bool needQuadUpdate;

    /**
     * Type of object in the map
     */
    const ObjectType objectType;
protected:
    /**
     * Position of the object on the map
     */
    CartesianCoordinates coordinates;

    /**
     * Dimensions on the map
     */
    ObjectSize dimensions;
};


#endif //MINIONCRUSHER_MAPOBJECT_H

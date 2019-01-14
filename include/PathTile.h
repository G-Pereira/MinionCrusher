/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */
#ifndef MINIONCRUSHER_PATHTILE_H
#define MINIONCRUSHER_PATHTILE_H

#include "MapObject.h"

class PathTile : public MapObject {
public:
    PathTile(float x, float y, float width, float height, const ObjectType type);

    PathTile(CartesianCoordinates coordinates, ObjectSize dimensions, const ObjectType type);

    const ObjectType &getType() const;    /// Get the direction of the tile

private:
};


#endif //MINIONCRUSHER_PATHTILE_H

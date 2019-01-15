#include "PathTile.h"

PathTile::PathTile(float x, float y, float width, float height, const ObjectType type)
        : MapObject(x, y, width, height, type) {

}

PathTile::PathTile(CartesianCoordinates coordinates, ObjectSize dimensions, const ObjectType type)
        : MapObject(coordinates, dimensions, nullptr, type) {

}

const ObjectType &PathTile::getType() const {
    return MapObject::objectType;
}


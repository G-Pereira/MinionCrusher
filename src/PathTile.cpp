/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include "PathTile.h"

PathTile::PathTile(float x, float y, float width, float height, const MapSlots type)
        : MapObject(x, y, width, height), type(type) {

}

PathTile::PathTile(CartesianCoordinates coordinates, ObjectSize dimensions, const MapSlots type)
        : MapObject(coordinates, dimensions), type(type) {

}

const MapSlots &PathTile::getType() const {
    return type;
}

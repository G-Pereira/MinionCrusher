/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include "MapObject.h"

MapObject::MapObject(float x, float y, float width, float height)
        : coordinates({x, y}), dimensions({width, height}) {
    texture = nullptr;
}

MapObject::MapObject(CartesianCoordinates coordinates, const ObjectSize dimensions)
        : coordinates(coordinates), dimensions(dimensions) {
    texture = nullptr;
    // No body yet
}

MapObject::~MapObject() {
    if (texture)
        SDL_DestroyTexture(texture);
}

const CartesianCoordinates &MapObject::getCoordinates() const {
    return this->coordinates;
}

void MapObject::setCoordinates(CartesianCoordinates inputCoordinates) {
    this->coordinates = inputCoordinates;
}

void MapObject::setCoordinates(float x, float y) {
    setCoordinates(CartesianCoordinates{x, y});
}

const ObjectSize &MapObject::getDimensions() const {
    return dimensions;
}

void MapObject::setDimensions(ObjectSize size) {
    dimensions = size;
}

SDL_Texture *MapObject::getTexture() const {
    return texture;
}

bool MapObject::setTexture(SDL_Texture *nTexture) {
    if (!nTexture)
        return false;
    texture = nTexture;
    return true;
}

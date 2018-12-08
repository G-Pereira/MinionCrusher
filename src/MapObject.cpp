/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include "MapObject.h"

MapObject::MapObject(float x, float y, float width, float height)
	: MapObject(CartesianCoordinates{x,y}, ObjectSize{ width, height }, nullptr) {
}

MapObject::MapObject(CartesianCoordinates coordinates, const ObjectSize dimensions, SDL_Texture * texture)
	:RenderElement(SDL_Rect{}, texture), coordinates(coordinates), dimensions(dimensions) {
}

MapObject::~MapObject() {
}

const CartesianCoordinates &MapObject::getCoordinates() const {
    return this->coordinates;
}

void MapObject::setCoordinates(CartesianCoordinates coordinates) {
    this->coordinates = coordinates;
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

void MapObject::Render(SDL_Renderer * renderer)
{

}

//SDL_Texture *MapObject::getTexture() const {
//    return texture;
//}
//
//bool MapObject::setTexture(SDL_Texture *nTexture) {
//    if (!nTexture)
//        return false;
//    texture = nTexture;
//    return true;
//}

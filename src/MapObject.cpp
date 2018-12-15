/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include "MapObject.h"

MapObject::MapObject(float x, float y, float width, float height)
        : MapObject(CartesianCoordinates{x, y}, ObjectSize{width, height}, nullptr) {
}

MapObject::MapObject(CartesianCoordinates coordinates, const ObjectSize dimensions, SDL_Texture *texture)
        : RenderElement(SDL_Rect{}, texture), coordinates(coordinates), dimensions(dimensions) {
}

MapObject::~MapObject() {
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

void MapObject::updateQuad(float tilewidth, float tileheight) {
    quad.w = (int) (dimensions.width * tilewidth);
    quad.h = (int) (dimensions.height * tileheight);
    quad.x = (int) (coordinates.x * tilewidth);
    quad.y = (int) (coordinates.y * tileheight);
}

void MapObject::Render(SDL_Renderer *renderer) {
    //Render texture to screen
    if (renderer) {
        if (background) {
            SDL_RenderCopy(renderer, background, nullptr, &quad);
        } else {
            SDL_SetRenderDrawColor(renderer, 0xAA, 0x00, 0xFF, 0xFF);
            SDL_RenderFillRect(renderer, &quad);
        }
    } else {
        throw std::runtime_error("No renderer passed to RenderElement::Render()!");
    }

    postRender(renderer);
}

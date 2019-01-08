/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */

#include "PathTile.h"

PathTile::PathTile(float x, float y, float width, float height, const ObjectType type)
        : MapObject(x, y, width, height), type(type) {

}

PathTile::PathTile(CartesianCoordinates coordinates, ObjectSize dimensions, const ObjectType type)
        : MapObject(coordinates, dimensions, nullptr), type(type) {

}

const ObjectType &PathTile::getType() const {
    return type;
}

void PathTile::render() {
    if (RenderElement::renderer) {
        if (background) {
            int dif = quad.h - quad.w;
            //render texture to screen
            SDL_RendererFlip flip = (SDL_RendererFlip) 0;
            double angle = 0.0;
            SDL_Rect quad_rotated = quad;
            switch (type) {
                case (ObjectType) 0:
                    break;
                case (ObjectType) 1:
                    flip = (SDL_RendererFlip) 1;
                    break;
                case (ObjectType) 2:
                    angle = 90.0;
                    quad_rotated.x = quad.x - dif / 2;
                    quad_rotated.y = quad.y + dif / 2;
                    quad_rotated.w = quad.h;
                    quad_rotated.h = quad.w;
                    break;
                case (ObjectType) 3:
                    angle = -90.0;
                    quad_rotated.x = quad.x - dif / 2;
                    quad_rotated.y = quad.y + dif / 2;
                    quad_rotated.w = quad.h;
                    quad_rotated.h = quad.w;
                    break;
                case (ObjectType) 4:
                    break;
            }
            SDL_RenderCopyEx(RenderElement::renderer, background, nullptr, &quad_rotated, angle, nullptr, flip);
        } else {
            SDL_SetRenderDrawColor(RenderElement::renderer, 0xAA, 0x00, 0xFF, 0xFF);
            SDL_RenderFillRect(RenderElement::renderer, &quad);
        }
    } else {
        throw std::runtime_error("No renderer passed to RenderElement::render()!");
    }

    postRender();
}

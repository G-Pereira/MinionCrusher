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
        : MapObject(coordinates, dimensions, nullptr), type(type) {

}

const MapSlots &PathTile::getType() const {
    return type;
}

void PathTile::Render(SDL_Renderer *renderer) {
    if (renderer) {
        if (background) {
            int dif = quad.h - quad.w;
            //Render texture to screen
            SDL_RendererFlip flip = (SDL_RendererFlip) 0;
            double angle = 0.0;
            SDL_Rect quad_rotated = quad;
            switch (type) {
                case (MapSlots) 0:
                    break;
                case (MapSlots) 1:
                    flip = (SDL_RendererFlip) 1;
                    break;
                case (MapSlots) 2:
                    angle = 90.0;
                    quad_rotated.x = quad.x - dif / 2;
                    quad_rotated.y = quad.y + dif / 2;
                    quad_rotated.w = quad.h;
                    quad_rotated.h = quad.w;
                    break;
                case (MapSlots) 3:
                    angle = -90.0;
                    quad_rotated.x = quad.x - dif / 2;
                    quad_rotated.y = quad.y + dif / 2;
                    quad_rotated.w = quad.h;
                    quad_rotated.h = quad.w;
                    break;
                case (MapSlots) 4:
                    break;
            }
            SDL_RenderCopyEx(renderer, background, nullptr, &quad_rotated, angle, nullptr, flip);
        } else {
            SDL_SetRenderDrawColor(renderer, 0xAA, 0x00, 0xFF, 0xFF);
            SDL_RenderFillRect(renderer, &quad);
        }
    } else {
        throw std::runtime_error("No renderer passed to RenderElement::Render()!");
    }

    postRender(renderer);
}

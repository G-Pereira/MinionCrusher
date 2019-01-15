#include "MapObject.h"

MapObject::MapObject(float x, float y, float width, float height, ObjectType type)
        : MapObject(CartesianCoordinates{x, y}, ObjectSize{width, height}, nullptr, type) {
}

MapObject::MapObject(CartesianCoordinates coordinates, const ObjectSize dimensions, SDL_Texture *texture,
                     ObjectType type)
        : RenderElement(SDL_Rect{}, texture), coordinates(coordinates), dimensions(dimensions),
          needQuadUpdate(true), objectType(type) {
}

MapObject::~MapObject() {
}

CartesianCoordinates MapObject::getCoordinates() {
    return this->coordinates;
}

void MapObject::setCoordinates(CartesianCoordinates inputCoordinates) {
    needQuadUpdate = true;
    this->coordinates = inputCoordinates;
}

void MapObject::setCoordinates(float x, float y) {
    setCoordinates(CartesianCoordinates{x, y});
}

const ObjectSize &MapObject::getDimensions() const {
    return dimensions;
}

void MapObject::setDimensions(ObjectSize size) {
    needQuadUpdate = true;
    dimensions = size;
}

void MapObject::updateQuad(float tilewidth, float tileheight) {
    quad.w = (int) (dimensions.width * tilewidth);
    quad.h = (int) (dimensions.height * tileheight);
    quad.x = (int) (coordinates.x * tilewidth);
    quad.y = (int) (coordinates.y * tileheight);
    needQuadUpdate = false;
}

void MapObject::render() {
    //render texture to screen
    //std::cout << "Rendering MapObject" << std::endl;
    if (RenderElement::renderer) {
        if (background || true) {
            int dif = quad.h - quad.w;
            //render texture to screen
            SDL_RendererFlip flip = (SDL_RendererFlip) 0;
            double angle = 0.0;
            SDL_Rect quad_rotated = quad;

            switch (objectType) {
                case ObjectType::BASE:
                    SDL_RenderCopy(RenderElement::renderer,
                                   RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::base), nullptr,
                                   &quad);
                    break;
                case ObjectType::MINIONMEDIUM:
                    SDL_RenderCopy(RenderElement::renderer,
                                   RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::minion), nullptr,
                                   &quad);
                    break;
                case ObjectType::MINIONREMI:
                    SDL_RenderCopy(RenderElement::renderer,
                                   RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::remi), nullptr,
                                   &quad);
                    break;
                case ObjectType::TOWER1:
                    SDL_RenderCopy(RenderElement::renderer,
                                   RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::tower1), nullptr,
                                   &quad);
                    break;
                case ObjectType::TOWER2:
                    SDL_RenderCopy(RenderElement::renderer,
                                   RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::tower2), nullptr,
                                   &quad);
                    break;
                case ObjectType::RIGHT:
                    flip = (SDL_RendererFlip) 1;
                    SDL_RenderCopyEx(RenderElement::renderer,
                                     RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::path), nullptr,
                                     &quad_rotated, angle, nullptr, flip);
                    break;
                case ObjectType::UP:
                    angle = 90.0;
                    quad_rotated.x = quad.x - dif / 2;
                    quad_rotated.y = quad.y + dif / 2;
                    quad_rotated.w = quad.h;
                    quad_rotated.h = quad.w;
                    SDL_RenderCopyEx(RenderElement::renderer,
                                     RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::path), nullptr,
                                     &quad_rotated, angle, nullptr, flip);
                    break;
                case ObjectType::DOWN:
                    angle = -90.0;
                    quad_rotated.x = quad.x - dif / 2;
                    quad_rotated.y = quad.y + dif / 2;
                    quad_rotated.w = quad.h;
                    quad_rotated.h = quad.w;
                    SDL_RenderCopyEx(RenderElement::renderer,
                                     RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::path), nullptr,
                                     &quad_rotated, angle, nullptr, flip);
                    break;
                case ObjectType::LEFT:
                    SDL_RenderCopyEx(RenderElement::renderer,
                                     RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::path), nullptr,
                                     &quad_rotated, angle, nullptr, flip);
                    break;
                default:
                    SDL_RenderCopy(RenderElement::renderer, background, nullptr, &quad);
            }
        } else {
            SDL_SetRenderDrawColor(RenderElement::renderer, 0xAA, 0x00, 0xFF, 0xFF);
            SDL_RenderFillRect(RenderElement::renderer, &quad);
        }
    } else {
        throw std::runtime_error("No renderer passed to RenderElement::render()!");
    }

    postRender();
}

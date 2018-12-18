#include "MapView.h"

MapView::MapView(SDL_Rect quad, UIElement *parent) : UIElement(quad, parent), map(nullptr), tilewidth(0),
                                                     tileheight(0) {

}

void MapView::postRender() {
    for (auto &path_tile : map->path) {
        if (!path_tile.hasTexture()) {
            path_tile.loadTexture("resources/sprites/path_tile.bmp", SDL_Color{0x00, 0xFF, 0xFF, 0xFF});
        }
        path_tile.updateQuad(tilewidth, tileheight);
        path_tile.render();
    }
    for (auto &minion : map->minions) {
        if (!minion.hasTexture()) {
            minion.loadTexture("resources/sprites/minion1.bmp", SDL_Color{0x00, 0xFF, 0xFF, 0xFF});
        }
        minion.updateQuad(tilewidth, tileheight);
        minion.render();
    }

    for (auto &tower : map->towers) {

        if (!tower.hasTexture()) {
            tower.loadTexture("resources/sprites/tower1_tile.bmp", SDL_Color{0x00, 0xFF, 0xFF, 0xFF});
        }
        tower.updateQuad(tilewidth, tileheight);
        tower.render();
    }

    map->base.updateQuad(tilewidth, tileheight);
    map->base.updateQuad(tilewidth, tileheight);
    map->base.render();
}


void MapView::setMap(Map *new_map) {
    map = new_map;

    tilewidth = (float) quad.w / (float) map->x_tiles;
    tileheight = (float) quad.h / (float) map->y_tiles;
}

SDL_Rect MapView::getHealthbar() {
    return SDL_Rect{(int) (tilewidth * 0.25F), (int) (tileheight - tileheight * 0.1F), (int) (tilewidth * 0.5F),
                    (int) (tileheight * 0.1F)};
}

MapView::~MapView() {

}

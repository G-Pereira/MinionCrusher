#include "MapView.h"

MapView::MapView(SDL_Rect quad, UIElement *parent) : UIElement(quad, parent), tilewidth(0.0F),
                                                     tileheight(0.0F) {

}

void MapView::postRender() {
	tilewidth = (float)quad.w / (float)gamemanager->map->x_tiles;
	tileheight = (float)quad.h / (float)gamemanager->map->y_tiles;
    for (auto &path_tile : gamemanager->map->path) {
        if (!path_tile.hasTexture()) {
            path_tile.loadTexture("resources/sprites/path_tile.bmp", SDL_Color{0x00, 0xFF, 0xFF, 0xFF});
        }
        path_tile.updateQuad(tilewidth, tileheight);
        path_tile.render();
    }
    for (auto &minion : gamemanager->map->minions) {
        if (!minion.hasTexture()) {
            minion.loadTexture("resources/sprites/minion1.bmp", SDL_Color{0x00, 0xFF, 0xFF, 0xFF});
        }
        minion.updateQuad(tilewidth, tileheight);
        minion.render();
    }

    for (auto &tower : gamemanager->map->towers) {

        if (!tower.hasTexture()) {
            tower.loadTexture("resources/sprites/tower1_tile.bmp", SDL_Color{0x00, 0xFF, 0xFF, 0xFF});
        }
        tower.updateQuad(tilewidth, tileheight);
        tower.render();
    }
	
	gamemanager->map->base.updateQuad(tilewidth, tileheight);
	gamemanager->map->base.updateQuad(tilewidth, tileheight);
	gamemanager->map->base.render();
}

SDL_Rect MapView::getHealthbar() {
    return SDL_Rect{(int) (tilewidth * 0.25F), (int) (tileheight - tileheight * 0.1F), (int) (tilewidth * 0.5F),
                    (int) (tileheight * 0.1F)};
}

MapView::~MapView() {

}

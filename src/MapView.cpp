#include "MapView.h"

MapView::MapView(SDL_Rect quad, UIElement * parent) :UIElement(quad, parent), map(nullptr), tilewidth(0), tileheight(0){

}

void MapView::postRender(SDL_Renderer * renderer)
{
	std::lock_guard<std::mutex> lock(map->getMutex());
	for (auto &path_tile : map->path) {
		if (!path_tile.hasTexture()) {
			path_tile.loadTexture(renderer, "resources/sprites/path_tile.bmp", SDL_Color{ 0x00, 0xFF, 0xFF,0xFF });
		}
		path_tile.updateQuad(tilewidth, tileheight);
		path_tile.Render(renderer);
	}
	for (auto &minion : map->minions) {
		if (!minion.hasTexture()) {
			minion.loadTexture(renderer, "resources/sprites/minion1.bmp", SDL_Color{ 0x00, 0xFF, 0xFF,0xFF });
		}
		minion.updateQuad(tilewidth, tileheight);
		minion.Render(renderer);
	}

	for (auto &tower : map->towers) {

		if (!tower.hasTexture()) {
			tower.loadTexture(renderer, "resources/sprites/tower1_tile.bmp", SDL_Color{ 0x00, 0xFF, 0xFF,0xFF });
		}
		tower.updateQuad(tilewidth, tileheight);
		tower.Render(renderer);
	}

	map->base.updateQuad(tilewidth, tileheight);
	map->base.updateQuad(tilewidth, tileheight);
	map->base.Render(renderer);
}



void  MapView::setMap(SDL_Renderer * renderer, Map * new_map)
{
	map = new_map;

	tilewidth = (float)quad.w / (float)map->x_tiles;
	tileheight = (float)quad.h / (float)map->y_tiles;
}

SDL_Rect MapView::getHealthbar()
{
	return SDL_Rect{ (int)(tilewidth*0.25F), (int)(tileheight- tileheight * 0.1F), (int)(tilewidth*0.5F), (int)(tileheight * 0.1F)};
}

MapView::~MapView()
{

}

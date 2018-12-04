#include "MapView.h"
#include "TileView.h"

MapView::MapView(SDL_Rect quad, UIView * parent) :UIView(quad, parent), map(nullptr), tilewidth(0), tileheight(0){

}

void MapView::postRender()
{
	for (auto minion : map->minions) {
		auto coordinates = minion.getCoordinates();
		auto dims = minion.getDimensions();

		SDL_Rect fillRect;
		fillRect.w = dims.width * tilewidth*0.8;
		fillRect.h = dims.height * tileheight*0.8;
		fillRect.x = coordinates.x * tilewidth + 0.1 * fillRect.w;
		fillRect.y = coordinates.y * tileheight + 0.1 * fillRect.h;
		//cout << fillRect.x << " " << fillRect.y << " " << fillRect.w << " " << fillRect.h << " " << endl;

		if (!minion.getTexture()) {
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &fillRect);//SDL_RenderCopy(renderer, map_object.texture, nullptr, &fillRect);
		}
		else {
			SDL_RenderCopy(renderer, minion.getTexture(), nullptr, &fillRect);
		}
	}
}



void  MapView::setMap(Map * new_map)
{
	map = new_map;

	tilewidth = quad.w / map->x_tiles;
	tileheight = quad.h / map->y_tiles;

	children.clear();
	for (uint8_t i = 0; i < map->path.size(); i++) {
		SDL_Rect quad;
		auto coordinates = map->path[i].getCoordinates();
		quad.x = coordinates.x * tilewidth;
		quad.y = coordinates.y * tileheight;
		auto dims = map->path[i].getDimensions();
		quad.w = dims.width * tilewidth;
		quad.h = dims.height * tileheight;

		TileView * child = new TileView(quad, map->path[i].getType(), this);
		child->loadTexture("resources/sprites/path_tile.bmp");
		addChild(child);
		//cout << "setting path tile textures " << i << endl;
		//cout << coordinates.x << " " << coordinates.y << endl;
		//cout << dims.height << " " << dims.width << endl;

	}
}

MapView::~MapView()
{
}

void MapView::preRender()
{
	SDL_RenderSetViewport(renderer, &quad);
}

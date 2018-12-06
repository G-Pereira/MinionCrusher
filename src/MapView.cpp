#include "MapView.h"

MapView::MapView(SDL_Rect quad, UIElement * parent) :UIElement(quad, parent), map(nullptr), tilewidth(0), tileheight(0){

}

void MapView::postRender()
{
	std::lock_guard<std::mutex> lock(map->getMutex());
	for (auto minion : map->minions) {
		auto coordinates = minion.getCoordinates();
		auto dims = minion.getDimensions();

		SDL_Rect fillRect;
		fillRect.w = (int)(dims.width * tilewidth*0.8);
		fillRect.h = (int)(dims.height * tileheight*0.8);
		fillRect.x = (int)(coordinates.x * tilewidth + 0.1 * fillRect.w);
		fillRect.y = (int)(coordinates.y * tileheight + 0.1 * fillRect.h);
		//cout << fillRect.x << " " << fillRect.y << " " << fillRect.w << " " << fillRect.h << " " << endl;

		if (!minion.getTexture()) {
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &fillRect);//SDL_RenderCopy(renderer, map_object.texture, nullptr, &fillRect);
		}
		else {
			SDL_RenderCopy(renderer, minion.getTexture(), nullptr, &fillRect);
		}
		SDL_Rect health_rect = getHealthbar();
		fillRect.x = (int)(health_rect.x + coordinates.x * tilewidth);
		fillRect.y = (int)(health_rect.y + coordinates.y * tileheight);
		fillRect.w = (int)(health_rect.w);
		fillRect.h = (int)(health_rect.h);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &fillRect);
		fillRect.w = (int)(fillRect.w * (minion.getHealth() > 0 ? minion.getHealth() : 0) / minion.getMaxHealth());
		SDL_SetRenderDrawColor(renderer,  0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &fillRect);
	}

	for (auto tower : map->towers) {
		auto coordinates = tower.getCoordinates();
		auto dims = tower.getDimensions();

		SDL_Rect fillRect;
		fillRect.w = (int)(dims.width * tilewidth*0.8);
		fillRect.h = (int)(dims.height * tileheight*0.8);
		fillRect.x = (int)(coordinates.x * tilewidth + 0.1 * fillRect.w);
		fillRect.y = (int)(coordinates.y * tileheight + 0.1 * fillRect.h);

		if (!tower.getTexture()) {
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
			SDL_RenderFillRect(renderer, &fillRect);
		}
		else {
			SDL_RenderCopy(renderer, tower.getTexture(), nullptr, &fillRect);
		}
	}
	auto coordinates = map->base.getCoordinates();
	auto dims = map->base.getDimensions();

	SDL_Rect fillRect;
	fillRect.w = (int)(dims.width * tilewidth*1.1);
	fillRect.h = (int)(dims.height * tileheight*1.1);
	fillRect.x = (int)(coordinates.x * tilewidth - 0.05 * fillRect.w);
	fillRect.y = (int)(coordinates.y * tileheight - 0.05 * fillRect.h);

	if (!map->base.getTexture()) {
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer, &fillRect);
	}
	else {
		SDL_RenderCopy(renderer, map->base.getTexture(), nullptr, &fillRect);
	}

	
}



void  MapView::setMap(Map * new_map)
{
	map = new_map;

	tilewidth = (float)quad.w / (float)map->x_tiles;
	tileheight = (float)quad.h / (float)map->y_tiles;

	children.clear();
	for (uint8_t i = 0; i < map->path.size(); i++) {
		SDL_Rect tile_quad;
		auto coordinates = map->path[i].getCoordinates();
		tile_quad.x = (int)(coordinates.x * tilewidth);
		tile_quad.y = (int)(coordinates.y * tileheight);
		auto dims = map->path[i].getDimensions();
		tile_quad.w = (int)(dims.width * tilewidth);
		tile_quad.h = (int)(dims.height * tileheight);

		TileView * child = new TileView(tile_quad, map->path[i].getType(), this);
		child->loadTexture("resources/sprites/path_tile.bmp");
		addChild(child);
		//cout << "setting path tile textures " << i << endl;
		//cout << coordinates.x << " " << coordinates.y << endl;
		//cout << dims.height << " " << dims.width << endl;

	}
}

SDL_Rect MapView::getHealthbar()
{
	return SDL_Rect{ (int)(tilewidth*0.25F), (int)(tileheight- tileheight * 0.1F), (int)(tilewidth*0.5F), (int)(tileheight * 0.1F)};
}

MapView::~MapView()
{
}

void MapView::preRender()
{
	SDL_RenderSetViewport(renderer, &quad);
}

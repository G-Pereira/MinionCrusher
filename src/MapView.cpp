#include "MapView.h"

MapView::MapView(SDL_Rect quad) :UIView(quad) {

}

bool MapView::setMap(Map * new_map)
{
	map = new_map;

	float tilewidth = quad.w / map->x_tiles;
	float tileheight = quad.h / map->y_tiles;
	//SDL_Texture * path_texture = loadTexture("resources/sprites/path_tile.bmp");
	for (uint8_t i = 0; i < map->path.size(); i++) {
		SDL_Rect quad;
		auto coordinates = map->path[i].getCoordinates();
		quad.x = coordinates.x * tilewidth;
		quad.y = coordinates.y * tileheight;
		auto dims = map->path[i].getDimensions();
		quad.w = dims.width * tilewidth;
		quad.h = dims.height * tileheight;

		UIView * child = new UIView(quad);
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

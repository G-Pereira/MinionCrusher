#include "MapView.h"
MapView::MapView(SDL_Rect quad, UIElement *parent) : UIElement(quad, parent), tilewidth(0.0F),
                                                     tileheight(0.0F){

	loadTexture(RenderElement::texture_lib->GetTexture(TextureLib::TextureEnum::map));
	SDL_AddEventWatch(MapView::mapClick, this);
}

void MapView::postRender() {
	if (gamemanager->map == nullptr) {
		std::cout << "no map to render\n";
		return;
	}
	tilewidth = (float)quad.w / (float)gamemanager->map->x_tiles;
	tileheight = (float)quad.h / (float)gamemanager->map->y_tiles;
    for (auto &path_tile : gamemanager->map->path) {
        path_tile.updateQuad(tilewidth, tileheight);
        path_tile.render();
    }
    for (auto &minion : gamemanager->map->minions) {
        minion.updateQuad(tilewidth, tileheight);
        minion.render();
    }

    for (auto &tower : gamemanager->map->towers) {
        tower.updateQuad(tilewidth, tileheight);
        tower.render();
    }
	
	gamemanager->map->base.updateQuad(tilewidth, tileheight);
	gamemanager->map->base.updateQuad(tilewidth, tileheight);
	gamemanager->map->base.render();
}

int MapView::mapClick(void * userdata, SDL_Event * e)
{
	if (userdata == nullptr) {
		return -1;
	}
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		MapView * mapview = reinterpret_cast<MapView *>(userdata);

		switch (mapview->last_button_type)
		{
		case ButtonTypes::idle:
			break;
		default:
			//Get mouse position
			int x = e->button.x;
			int y = e->button.y;
			//SDL_GetMouseState(&x, &y);
			// go through this object and all parents to substracct the total offset
			UIElement *UI_elem = mapview;
			while (UI_elem) {
				x -= UI_elem->getQuad().x;
				y -= UI_elem->getQuad().y;
				UI_elem = UI_elem->getParent();
			}

			CartesianCoordinates coors;
			coors.x = floor(e->button.x / mapview->tilewidth);
			coors.y = floor(e->button.y / mapview->tileheight);
			if (gamemanager->addTower(coors, mapview->last_button_type)) {
				mapview->last_button_type = ButtonTypes::idle;
			}
			break;
		}
	}
	return 0;
}

SDL_Rect MapView::getHealthbar() {
    return SDL_Rect{(int) (tilewidth * 0.25F), (int) (tileheight - tileheight * 0.1F), (int) (tilewidth * 0.5F),
                    (int) (tileheight * 0.1F)};
}

MapView::~MapView() {

}

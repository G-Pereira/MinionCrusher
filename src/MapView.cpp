#include "MapView.h"
MapView::towerBuildingStates MapView::buildstate = MapView::towerBuildingStates::idle;

MapView::MapView(SDL_Rect quad, UIElement *parent) : UIElement(quad, parent), tilewidth(0.0F),
                                                     tileheight(0.0F){
	SDL_AddEventWatch(MapView::mapClick, this);
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

int MapView::setBuildTowerState(void * data, SDL_Event * e)
{
	if (gamemanager) {
		switch (buildstate) {
		case towerBuildingStates::idle:
			buildstate = towerBuildingStates::building;
			break;
		case towerBuildingStates::building:
			break;
		}
	}
	else {
		std::cout << "no gamemanager\n";
	}
	return 0;
}

int MapView::mapClick(void * userdata, SDL_Event * e)
{
	if (userdata == nullptr) {
		return -1;
	}
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		MapView * mapview = reinterpret_cast<MapView *>(userdata);
		UIElement *UI_elem = mapview;

		switch (mapview->buildstate)
		{
		case MapView::towerBuildingStates::idle:
			break;
		case MapView::towerBuildingStates::building:
			//Get mouse position
			int x = e->button.x;
			int y = e->button.y;
			//SDL_GetMouseState(&x, &y);
			// go through this object and all parents to substracct the total offset
			while (UI_elem) {
				x -= UI_elem->getQuad().x;
				y -= UI_elem->getQuad().y;
				UI_elem = UI_elem->getParent();
			}

			CartesianCoordinates coors;
			coors.x = floor(e->button.x / mapview->tilewidth);
			coors.y = floor(e->button.y / mapview->tileheight);
			if (mapview->addTowerToMap(coors)) {
			}
			break;
		}
	}
	return 0;
}

bool MapView::addTowerToMap(CartesianCoordinates coordinates)
{
	bool retval = gamemanager->map->addTower(coordinates);
	if(retval)
		buildstate = MapView::towerBuildingStates::idle;
	return retval;
}

SDL_Rect MapView::getHealthbar() {
    return SDL_Rect{(int) (tilewidth * 0.25F), (int) (tileheight - tileheight * 0.1F), (int) (tilewidth * 0.5F),
                    (int) (tileheight * 0.1F)};
}

MapView::~MapView() {

}

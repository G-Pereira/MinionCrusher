/**
 * Author: Leon Klute
 * Created on: 26-11-18
 * Last Modified: 28-11-18
 */

#include <iostream>
#include "UI.h"

using namespace std;


//struct sdl_deleter
//{
//	void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
//	void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
//	void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
//};

UI::UI(int w, int h) : width(w), height(h) {
    window = nullptr;
    renderer = nullptr;
    map_texture = nullptr;
    buildings_texture = nullptr;
    info_texture = nullptr;
    map = nullptr;
    buttons[static_cast<int>(viewPorts::buildingsview)] = vector<UIButton>();
    buttons[static_cast<int>(viewPorts::infoview)] = vector<UIButton>();
    buttons[static_cast<int>(viewPorts::mapview)] = vector<UIButton>();

    buildingViewport = SDL_Rect();
    infoViewport = SDL_Rect();
    mapViewport = SDL_Rect();

}

UI::~UI() {
    close();
}

void UI::init() {
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error("SDL could not initialize!");

    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        throw std::runtime_error("Warning: Linear texture filtering not enabled!");

    // Create a Window in the middle of the screen
    window = SDL_CreateWindow("MinionCrusher", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width,
                              height, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        throw std::runtime_error("Window could not be created!");

    // Create a new renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        throw std::runtime_error("Renderer could not be created!");

    //Initialize renderer color
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);


    /* ratio of UI elements
    current shape:
    _________________
    |			|b	|
    |			|u	|
    |	map		|i	|
    |			|l	|
    |			|d	|
    |			|i	|
    |___________|n	|
    |	info	|g	|
    |___________|s__|
    */
    mapViewport.x = 0;
    mapViewport.y = 0;
    mapViewport.w = width * 8 / 10;
    mapViewport.h = height * 8 / 10;

    buildingViewport.x = width * 8 / 10;
    buildingViewport.y = 0;
    buildingViewport.w = width * 2 / 10;
    buildingViewport.h = height;

    infoViewport.x = 0;
    infoViewport.y = height * 8 / 10;
    infoViewport.w = width * 8 / 10;
    infoViewport.h = height * 2 / 10;


    map_texture = loadTexture("resources/sprites/map_background.bmp");
    info_texture = loadTexture("resources/sprites/info.bmp");
    buildings_texture = loadTexture("resources/sprites/right_side.bmp");
}

void UI::SetMap(Map *new_map) {
    map = new_map;

    float tilewidth = mapViewport.w / map->x_tiles;
    float tileheight = mapViewport.h / map->y_tiles;
    SDL_Texture *path_texture = loadTexture("resources/sprites/path_tile.bmp");
    for (uint8_t i = 0; i < map->path.size(); i++) {
        map->path[i].setTexture(path_texture);
        auto coordinates = map->path[i].getCoordinates();
        coordinates.x *= tilewidth;
        coordinates.y *= tileheight;
        map->path[i].setCoordinates(coordinates);
        auto dims = map->path[i].getDimensions();
        dims.width *= tilewidth;
        dims.height *= tileheight;
        map->path[i].setDimensions(dims);
        //cout << "setting path tile textures " << i << endl;
        //cout << coordinates.x << " " << coordinates.y << endl;
        //cout << dims.height << " " << dims.width << endl;

    }
}

void UI::AddButton(viewPorts port, SDL_Rect rect, SDL_Texture *texture, void funct(UIButton &self, SDL_Event &)) {
    buttons[static_cast<int>(port)].push_back(UIButton(rect, texture, texture, texture, texture, funct));
}

void UI::close() {
    //Free loaded images
    SDL_DestroyTexture(map_texture);
    map_texture = nullptr;
    SDL_DestroyTexture(info_texture);
    info_texture = nullptr;
    SDL_DestroyTexture(buildings_texture);
    buildings_texture = nullptr;

    //Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    //Quit SDL subsystems
    //IMG_Quit();
    SDL_Quit();
}

void UI::Render(/*MapObjects*/) {
    //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //SDL_RenderClear(renderer);
    RenderMap();

    //Building viewport
    SDL_RenderSetViewport(renderer, &buildingViewport);

    //Render texture to screen
    SDL_RenderCopy(renderer, buildings_texture, nullptr, nullptr);
    for (auto button : buttons[static_cast<int>(viewPorts::buildingsview)]) {
        button.render(renderer);
    }

    //info viewport
    SDL_RenderSetViewport(renderer, &infoViewport);


    //Render texture to screen
    SDL_RenderCopy(renderer, info_texture, nullptr, nullptr);


    //Update screen
    SDL_RenderPresent(renderer);
}

void UI::RenderMap() {
    //Top left corner viewport
    SDL_RenderSetViewport(renderer, &mapViewport);

    //Render background texture to screen
    SDL_RenderCopy(renderer, map_texture, nullptr, nullptr);

    if (!map) {
        cout << "no map initialized" << endl;
        return;
    }
    //render path tiles
    for (auto &path_tile  : map->path) {
        auto coordinates = path_tile.getCoordinates();
        auto dims = path_tile.getDimensions();
        SDL_Rect fillRect = {(int) coordinates.x, (int) coordinates.y, (int) dims.width, (int) dims.height};
        //cout << fillRect.x << " " << fillRect.y << " " << fillRect.w << " " << fillRect.h << " " << endl;

        if (!path_tile.getTexture()) {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &fillRect);//SDL_RenderCopy(renderer, map_object.texture, nullptr, &fillRect);
        } else {
            SDL_RendererFlip flip = (SDL_RendererFlip) 0;
            double angle = 0.0;
            switch (path_tile.getType()) {
                case (MapSlots) 0:
                    break;
                case (MapSlots) 1:
                    break;
                case (MapSlots) 2:
                    angle = 90.0;
                    break;
                case (MapSlots) 3:
                    angle = -90.0;
                    break;
                case (MapSlots) 4:
                    flip = (SDL_RendererFlip) 2;
                    break;
            }
            SDL_RenderCopyEx(renderer, path_tile.getTexture(), nullptr, &fillRect, angle, nullptr, flip);
        }
    }
    //render minions
    float tilewidth = mapViewport.w / map->x_tiles;
    float tileheight = mapViewport.h / map->y_tiles;
    for (auto &map_object : map->minions) {
        auto coordinates = map_object.getCoordinates();
        auto dims = map_object.getDimensions();

        SDL_Rect fillRect = {int(coordinates.x * tilewidth), int(coordinates.y * tileheight),
                             int(dims.width * tilewidth), int(dims.height * tileheight)};
        //cout << fillRect.x << " " << fillRect.y << " " << fillRect.w << " " << fillRect.h << " " << endl;

        if (!map_object.getTexture()) {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &fillRect);//SDL_RenderCopy(renderer, map_object.texture, nullptr, &fillRect);
        } else {
            SDL_RenderCopy(renderer, map_object.getTexture(), nullptr, &fillRect);
        }
    }

}

SDL_Renderer *UI::getRenderer() const {
    return renderer;
}

SDL_Texture *UI::loadTexture(std::string path) {
    //The final texture
    SDL_Texture *newTexture = nullptr;

    //Load image at specified path
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void UI::HandleButtons(SDL_Event &e) {
    for (auto building_button : buttons[static_cast<int>(viewPorts::buildingsview)]) {
        building_button.handleEvent(&e);
    }
}


const SDL_Rect UI::getMapViewport() const {
    return mapViewport;
}

const SDL_Rect UI::getInfoViewport() const {
    return infoViewport;
}

const SDL_Rect UI::getBuildingViewport() const {
    return buildingViewport;
}

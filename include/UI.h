#pragma once
#include <SDL.h>
#include <string>
#include <vector>

class Position {
public:
	Position(float x=0,float y=0) :x(x), y(y) {

	}
	float x;
	float y;
};
class MapObject {
public:
	MapObject(Position pos) :pos(pos) {

	}
	Position pos;
private:


};
class UI {
public:
	UI(int w, int h);
	~UI();
	bool init();
	void Render(SDL_Texture* Map, SDL_Texture* info, SDL_Texture* buildings);
	void RenderMap(SDL_Texture* Map, std::vector<MapObject*> map_objects);
	SDL_Renderer *getRenderer() const;

	SDL_Texture * loadTexture(std::string path);

private:
	void close();
	SDL_Window *window;
	SDL_Renderer *renderer;
	int width;
	int height;
	SDL_Rect mapViewport;
	SDL_Rect infoViewport;
	SDL_Rect buildingViewport;
};
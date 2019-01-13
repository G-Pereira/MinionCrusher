#include "TextureLib.h"



TextureLib::TextureLib(SDL_Renderer * renderer) : renderer(renderer), state(States::uninitialized)
{
	loadTexture("resources/sprites/base.bmp",			SDL_Color{ 34, 177, 76, 0xFF });
	loadTexture("resources/sprites/info.bmp",			SDL_Color{ 34, 177, 76, 0xFF });
	loadTexture("resources/sprites/map_background.bmp", SDL_Color{ 0 });
	loadTexture("resources/sprites/minion1.bmp",		SDL_Color{ 0x00, 0xFF, 0xFF, 0xFF });
	loadTexture("resources/sprites/rj.bmp",				SDL_Color{ 0x00, 0xFF, 0xFF, 0xFF });
	loadTexture("resources/sprites/path_tile.bmp",		SDL_Color{ 34, 177, 76, 0xFF });
	loadTexture("resources/sprites/right_side.bmp",		SDL_Color{ 34, 177, 76, 0xFF });
	loadTexture("resources/sprites/tower1_tile.bmp",	SDL_Color{ 34, 177, 76, 0xFF });
	loadTexture("resources/sprites/tower2_tile.bmp",	SDL_Color{ 34, 177, 76, 0xFF });
	loadTexture("resources/sprites/tower3_tile.bmp",	SDL_Color{ 34, 177, 76, 0xFF });

	state = States::initialized;
}


TextureLib::~TextureLib()
{
}

void TextureLib::loadTexture(std::string path, SDL_Color color) {
	//The final texture
	SDL_Texture *newTexture = nullptr;

	//Load image at specified path
	SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == nullptr) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());

	}
	else {
		//Create texture from surface pixels
		if (color.a > 0) {
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, color.r, color.g, color.b));
		}
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	textures.push_back(newTexture);
	//background = newTexture;
}

SDL_Texture * TextureLib::GetTexture(TextureEnum texturename)
{
	if (state != States::initialized) {
		std::cout << "TextureLib was not initialized when used\n";
		return nullptr;
	}
	if ((int)texturename > textures.size()) {
		std::cout << "index was out of range\n";
		return nullptr;
	}
	return textures[(int)texturename];
}

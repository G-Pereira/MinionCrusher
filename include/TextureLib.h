/**
 * TextureLib handles the loading and deletion of the textures
 * it supplies them by easily accesible names in an enum
 */


#pragma once


#include <string>
#include <vector>
#include <iostream>

#ifdef _WIN32
#include <SDL_ttf.h>
#include <SDL.h>
#else

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

#endif

class TextureLib
{
public:
	TextureLib(SDL_Renderer * renderer);
	~TextureLib();


	enum class TextureEnum : int {
		base,
		info,
		map,
		minion,
		remi,
		path,
		building_background,
		tower1,
		tower2,
		tower3,
		menu,
	};

	enum class States {
		uninitialized,
		initialized,
		error
	} state;
	SDL_Texture * GetTexture(TextureEnum texturename);

private:
	void loadTexture(std::string path, SDL_Color color);
	std::vector<SDL_Texture *> textures;

	SDL_Renderer * renderer;
};


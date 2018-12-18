
#include <UIText.h>

#include "UIText.h"

UIText::UIText(SDL_Rect quad, UIElement *parent) :
        UIElement(quad, parent) {
}

void UIText::loadTexture(std::string text)
{
    if(TTF_Init()==-1) {
        std::cout << "TTF_Init: " << TTF_GetError();
        exit(2);
    }
	//The final texture
	SDL_Texture *newTexture = nullptr;

	//Load image at specified path
	TTF_Font* Sans = TTF_OpenFont("resources/fonts/lazy.ttf", 24); //this opens a font style and sets a size

	std::cout << TTF_GetError(); // prints 0

	SDL_Color White = { 255, 255, 255 , 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	if (surfaceMessage == nullptr) {
		printf("Unable to load text into surface");
	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(this->renderer, surfaceMessage);
		if (newTexture == nullptr) {
			printf("Unable to create texture from %s! SDL Error: %s\n", text.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(surfaceMessage);
	}

	background = newTexture;

}

UIText::~UIText() {
}
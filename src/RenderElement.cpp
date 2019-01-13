#include "RenderElement.h"

SDL_Renderer* RenderElement::renderer = nullptr;

TextureLib * RenderElement::texture_lib = nullptr;

RenderElement::RenderElement(SDL_Rect quad, SDL_Texture *texture) : quad(quad), background(texture) {

}

RenderElement::RenderElement(SDL_Rect quad) : RenderElement(quad, nullptr) {

}

RenderElement::~RenderElement() {
    //Free loaded images
    //SDL_DestroyTexture(background);
}

void RenderElement::postRender() {
}

void RenderElement::loadTexture(SDL_Texture *texture) {
    background = texture;
}

void RenderElement::loadText2Texture(std::string text)
{
	if (background != nullptr) {
		SDL_DestroyTexture(background);
	}
	//The final texture
	SDL_Texture *newTexture = nullptr;

	//Load image at specified path
	TTF_Font* Sans = TTF_OpenFont("resources/fonts/pixel.otf", 90); //this opens a font style and sets a size

	std::cout << TTF_GetError(); // prints 0

	SDL_Color White = { 255, 255, 255 , 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

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
	TTF_CloseFont(Sans);

}

//void RenderElement::setQuad(SDL_Rect new_quad)
//{
//	quad = new_quad;
//}
//
SDL_Rect &RenderElement::getQuad() {
    return quad;
}


bool RenderElement::hasTexture() {
    return background ? true : false;
}

#include "RenderElement.h"


RenderElement::RenderElement(SDL_Rect quad, SDL_Texture * texture) : quad(quad), background(texture) {

}
RenderElement::RenderElement(SDL_Rect quad) :RenderElement(quad, nullptr){

}

RenderElement::~RenderElement()
{
	//Free loaded images
	SDL_DestroyTexture(background);
}

void RenderElement::postRender(SDL_Renderer * renderer)
{
	//SDL_assert(renderer);
}

void RenderElement::loadTexture(SDL_Renderer * renderer, std::string path)
{
	loadTexture(renderer, path, SDL_Color{ 0,0,0,0 });
}

void RenderElement::loadTexture(SDL_Renderer * renderer, std::string path, SDL_Color color)
{
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Create texture from surface pixels
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, color.r, color.g, color.b));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	background = newTexture;
}

void RenderElement::loadTexture(SDL_Texture * texture)
{
	background = texture;
}

//void RenderElement::setQuad(SDL_Rect new_quad)
//{
//	quad = new_quad;
//}
//
SDL_Rect& RenderElement::getQuad()
{
	return quad;
}


bool RenderElement::hasTexture()
{
	return background ? true : false;
}

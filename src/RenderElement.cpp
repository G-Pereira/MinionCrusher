#include "RenderElement.h"


RenderElement::RenderElement(SDL_Rect quad, SDL_Texture * texture) : quad(quad), background(texture) {

}
RenderElement::RenderElement(SDL_Rect quad) :RenderElement(quad, nullptr){

}

RenderElement::~RenderElement()
{
	close();
}

void RenderElement::preRender(SDL_Renderer * renderer)
{
}

void RenderElement::postRender(SDL_Renderer * renderer)
{
}

void RenderElement::loadTexture(SDL_Renderer * renderer, std::string path)
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

void RenderElement::setQuad(SDL_Rect new_quad)
{
	quad = new_quad;
}

SDL_Rect RenderElement::getQuad()
{
	return quad;
}


bool RenderElement::hasTexture()
{
	return background ? true : false;
}

void RenderElement::close()
{
	//Free loaded images
	SDL_DestroyTexture(background);
	background = nullptr;

}

void RenderElement::Render(SDL_Renderer * renderer)
{
	preRender(renderer);
	//Render texture to screen
	if (renderer) {
		if (background) {
			SDL_RenderCopy(renderer, background, nullptr, &quad);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0xAA, 0x00, 0xFF, 0xFF);
			SDL_RenderFillRect(renderer, &quad);
		}
	}
	else {
		throw std::runtime_error("No renderer passed to RenderElement::Render()!");
	}

	postRender(renderer);
}

//SDL_Renderer * RenderElement::getRenderer() const
//{
//	return renderer;
//}

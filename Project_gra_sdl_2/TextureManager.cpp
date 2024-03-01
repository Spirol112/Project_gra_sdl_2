#include "TextureManager.h"

SDL_Texture* TextureManager::load_texture(const char* file_name)
{
	SDL_Surface* temp_surface = IMG_Load(file_name);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest,NULL,NULL,flip);
}

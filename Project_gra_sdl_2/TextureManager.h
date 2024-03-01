#pragma once
#include"Game.h"

class TextureManager
{
private:
	

public:
	static SDL_Texture* load_texture(const char* file_name);
	static void draw(SDL_Texture* tex,SDL_Rect src, SDL_Rect dest,SDL_RendererFlip flip);
};


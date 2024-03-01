#include "GameObject.h"
#include"TextureManager.h"

GameObject::GameObject(const char* texture_sheet, int x,int y)
{
	obj_tex = TextureManager::load_texture(texture_sheet);

	xpos = x;
	ypos = y;
}

void GameObject::update()
{
	xpos++;
	ypos++;

	src_rect.h = 32;
	src_rect.w = 32;
	src_rect.x = 0;
	src_rect.y = 0;

	dest_rect.h = src_rect.h * 2;
	dest_rect.w = src_rect.w * 2;
	dest_rect.x = xpos;
	dest_rect.y = ypos;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, obj_tex, &src_rect, &dest_rect);
}

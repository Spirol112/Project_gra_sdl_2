#pragma once
#include"Game.h"

class GameObject
{
private:
	int xpos{};
	int ypos{};

	SDL_Texture* obj_tex{};
	SDL_Rect src_rect, dest_rect;
public:
	GameObject(const char* texture_sheet,int x,int y);
	~GameObject();

	void update();
	void render();
};


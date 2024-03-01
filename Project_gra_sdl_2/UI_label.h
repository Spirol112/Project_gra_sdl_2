#pragma once

#include"ECS.h"
#include"Asset_manager.h"
#include"Game.h"
#include"SDL.h"
#include"SDL_ttf.h"
#include<string>


class UI_label : public Component
{
private:
	SDL_Rect position;
	std::string label_text;
	std::string label_font;
	SDL_Color text_colour;
	SDL_Texture* label_texture;

public:
	UI_label(int xpos, int ypos,std::string text, std::string font,SDL_Color& colour) : 
		label_text(text),label_font(font),text_colour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		set_label_text(label_text,label_font);
	}
	~UI_label()
	{}

	void set_label_text(std::string l_text,std::string l_font)
	{
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->get_font(l_font), l_text.c_str(), text_colour);
		label_texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(label_texture, nullptr, nullptr, &position.w, &position.h);
	}

	void draw()override
	{
		SDL_RenderCopy(Game::renderer, label_texture, nullptr, &position);
	}

	void update()override
	{

	}
};
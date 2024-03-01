#pragma once
#include"ECS.h"
#include"SDL.h"
#include"TextureManager.h"
#include"Game.h"

class Asset_manager;

class Tile_component :public Component
{
private:

public:

	SDL_Texture* texture;
	SDL_Rect src_rec;
	SDL_Rect dst_rec;
	Vector_2D position;

	Tile_component() = default;

	~Tile_component()
	{
		SDL_DestroyTexture(texture);
	}

	Tile_component(int src_x,int src_y,int xpos,int ypos,int t_size,int t_scale, std::string id)
	{
		texture = Game::assets->get_texture(id);

		position.x = xpos;
		position.y = ypos;

		src_rec.x = src_x;
		src_rec.y = src_y;
		src_rec.w = t_size;
		src_rec.h = t_size;

		dst_rec.x = xpos;
		dst_rec.y = ypos;
		dst_rec.w = t_size * t_scale;
		dst_rec.h = t_size * t_scale;
	}
	/*Tile_component(int src_x, int src_y, int xpos, int ypos, int t_size, int t_scale, const char* path)
	{
		texture = TextureManager::load_texture(path);

		position.x = xpos;
		position.y = ypos;

		src_rec.x = src_x;
		src_rec.y = src_y;
		src_rec.w = t_size;
		src_rec.h = t_size;

		dst_rec.x = xpos;
		dst_rec.y = ypos;
		dst_rec.w = t_size * t_scale;
		dst_rec.h = t_size * t_scale;
	}*/

	void update()override
	{
		dst_rec.x = position.x - Game::camera.x;
		dst_rec.y = position.y - Game::camera.y;
	}

	void draw()override
	{
		TextureManager::draw(texture, src_rec, dst_rec,SDL_FLIP_NONE);
	}
	
};
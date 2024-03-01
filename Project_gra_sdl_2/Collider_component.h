#pragma once
#include<string>
#include"SDL.h"
#include"ECS.h"
#include"Components.h"
#include<vector>
#include"TextureManager.h"

class Collider_component : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect src_r;
	SDL_Rect dst_r;

	Transform_component* transform;

	Collider_component(std::string t)
	{
		tag = t;
	}

	Collider_component(std::string t,int xpos,int ypos,int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = size;
		collider.w = size;
	}


	void init()override
	{
		if (!entity->has_component<Transform_component>())
		{
			entity->add_component<Transform_component>();
		}
		transform = &entity->get_comp<Transform_component>();

		tex = TextureManager::load_texture("assets/coll_tex.png");

		src_r = { 0,0,32,32 };
		dst_r = { collider.x,collider.y,collider.w,collider.h };
	}

	void update()override
	{
		if (tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		dst_r.x = collider.x - Game::camera.x;
		dst_r.y = collider.y - Game::camera.y;
	}
	void draw()override
	{
		TextureManager::draw(tex, src_r, dst_r, SDL_FLIP_NONE);
	}

};


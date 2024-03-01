#pragma once
#include"Components.h"
#include"SDL.h"
#include"TextureManager.h"
#include"Animation.h"
#include<map>
#include"Asset_manager.h"
//#include"Game.h"

class Asset_manager;

class Sprite_component:public Component
{
private:
	Transform_component *transform;
	SDL_Texture* texture;
	SDL_Rect src_rect;
	SDL_Rect dest_rect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	int anim_index = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

	Sprite_component() = default;

	Sprite_component(std::string id)
	{
		set_tex(id);
	}

	Sprite_component(std::string id ,bool is_animated)
	{
		animated = is_animated;
		Animation idle = Animation(0, 4, 100);
		Animation walk = Animation(1, 8, 70);
		Animation idle_site = Animation(2, 4, 100);
		Animation walk_down = Animation(3, 4, 70);
		Animation walk_up = Animation(4, 4, 70);
	
		animations.emplace("idle", idle);
		animations.emplace("walk", walk);
		animations.emplace("idle_site", idle_site);
		animations.emplace("walk_up", walk_up);
		animations.emplace("walk_down", walk_down);

		Animation skeleton_idle = Animation(1, 10, 90);
		Animation skeleton_walk = Animation(2, 10, 80);
		Animation skeleton_death = Animation(4, 10, 140);
		animations.emplace("enemy_idle", skeleton_idle);
		animations.emplace("enemy_walk", skeleton_walk);
		animations.emplace("enemy_death", skeleton_death);

		if (id == "player")
		{
			play("idle");
		}
		if (id == "skeleton")
		{
			play("enemy_idle");
		}
		if (id == "fire_skeleton")
		{
			play("enemy_idle");
		}
		set_tex(id);
	}

	~Sprite_component()
	{
	}
	void set_tex(std::string id)
	{
		texture = Game::assets->get_texture(id);
	}

	void init()override
	{
		transform = &entity->get_comp<Transform_component>();

		src_rect.x = 0;
		src_rect.y = 0;
		src_rect.w = transform->width;
		src_rect.h = transform->height;
	}
	void update()override
	{
		if (animated)
		{
			src_rect.x = src_rect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		src_rect.y = anim_index * src_rect.h;

		dest_rect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		dest_rect.y = static_cast<int>(transform->position.y) - Game::camera.y;

		dest_rect.w = static_cast<int>(transform->width*transform->scale);
		dest_rect.h = static_cast<int>(transform->height * transform->scale);
	}
	void draw()override
	{
		TextureManager::draw(texture, src_rect, dest_rect,sprite_flip);
	}
	int get_feames(void) { return frames; }
	void set_frames(int mf) { frames = mf; }
	SDL_Rect get_src_rect() { return src_rect; }
	void set_src_rect_x(int x) { src_rect.x = x; }
	void play(const char* anim_name)
	{
		frames = animations[anim_name].frames;
		speed = animations[anim_name].speed;
		anim_index = animations[anim_name].index;
	}
	void set_animated(bool anim) { animated = anim; }
	void death_anim()
	{

	}
};


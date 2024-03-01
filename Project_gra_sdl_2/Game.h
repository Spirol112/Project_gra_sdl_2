#pragma once

#include"SDL.h"
#include <iostream>
#include"SDL_image.h"
#include<vector>


class Asset_manager;
class Collider_component;


class Game
{
private:
	
	
	SDL_Window* window{};

public:
	Game();
	~Game();

	static bool is_running;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static SDL_Rect camera;
	static Asset_manager* assets;

	enum group_labels : std::size_t
	{
		group_map,
		group_players,
		group_colliders,
		group_projectiles,
		group_enemis
	};

	void init(const char* title, int xpos, int ypos, int width, int height, bool full_screen);
	void handel_events();
	void update();
	void render();
	void cleen();
	bool running() { return is_running; }
};


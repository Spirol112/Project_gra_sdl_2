#include "Game.h"
#include "TextureManager.h"
#include"Map.h"
#include"Components.h"
#include"Vector_2D.h"
#include "Collision.h"
#include<vector>
#include "Asset_manager.h"
#include<sstream>

//defaining
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Surface *icon{};

Map* map;
Manager manager;



SDL_Rect Game::camera = { 0,0,3840,4160};

Asset_manager* Game::assets = new Asset_manager(&manager);

bool Game::is_running = false;

auto& player(manager.add_entity());
auto& skeleton(manager.add_entity());
auto& fire_skeleton(manager.add_entity());
auto& label(manager.add_entity());

Game::Game(){}
Game::~Game(){} 
//initialising game 
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool full_screen)
{
	int flags = 0;
	if (full_screen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	//initialising SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "...Subsystem Initialised..." << std::endl;
		//creating game window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "...Window created..." << std::endl;
		}
		//creating renderer
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "...Renderer created..." << std::endl;
		}
		icon = IMG_Load("assets/game_icon.ico");
		SDL_SetWindowIcon(window, icon);
		is_running = true;
	}
	else { is_running = false; }

	if (TTF_Init() == -1)
	{
		std::cout << "...Error : SDL_TTF failed to inicialize" << std::endl;
	}
	//assets
	assets->add_font("arial", "assets/arial.ttf",16);
	assets->add_texture("terrain", "assets/tile_set_03.png");
	assets->add_texture("player", "assets/Wizzard_anime.png");
	assets->add_texture("projectile", "assets/proj.png");
	assets->add_texture("skeleton", "assets/skeleton_anime.png");
	assets->add_texture("fire_skeleton", "assets/fire_skeleton_anime.png");
	//map
	map = new Map("terrain", 3, 32);
	map->load_map("assets/map_50x50_V2.map", 50, 50);
	//ecs implementation
	player.add_component<Transform_component>(380,420,32,32,3);
	player.add_component<Sprite_component>("player",true);
	player.add_component<Keyboard_controller>();
	player.add_component<Collider_component>("player");
	player.add_group(group_players);

	skeleton.add_component<Transform_component>(1600, 420, 32, 32, 4);
	skeleton.add_component<Sprite_component>("skeleton", true);
	skeleton.add_component<Collider_component>("skeleton");
	skeleton.add_component<Enemy_skeleton>();
	skeleton.add_group(group_enemis);

	fire_skeleton.add_component<Transform_component>(2100, 2750, 32, 32, 4);
	fire_skeleton.add_component<Sprite_component>("fire_skeleton", true);
	fire_skeleton.add_component<Collider_component>("fire_skeleton");
	fire_skeleton.add_component<Fire_enemy_skeleton>();
	fire_skeleton.add_group(group_enemis);
	//UI/font
	SDL_Color white = { 255,255,255,255 };
	label.add_component<UI_label>(10, 10, "Test", "arial", white);
	//projectiles
	
}
//groups
auto& tiles(manager.get_group(Game::group_map));
auto& players(manager.get_group(Game::group_players));
auto& colliders(manager.get_group(Game::group_colliders));
auto& projectiles(manager.get_group(Game::group_projectiles));
auto& enemis(manager.get_group(Game::group_enemis));
//handeling events
void Game::handel_events()
{
	SDL_PollEvent(&event);
	//quiting game
	switch (event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;
	default:
		break;
	}
}
//updates
void Game::update()
{
	//player update
	SDL_Rect player_col = player.get_comp<Collider_component>().collider;
	SDL_Rect skel_col = skeleton.get_comp<Collider_component>().collider;
	SDL_Rect fire_skel_col = fire_skeleton.get_comp<Collider_component>().collider;
	Vector_2D player_pos = player.get_comp<Transform_component>().position;
	//UI update
	std::stringstream ss;
	ss << "Player position: " << player.get_comp<Transform_component>().position;
	label.get_comp<UI_label>().set_label_text(ss.str(), "arial");
	//manager update
	manager.refresh();
	manager.update();
	//collision update
	for (auto& c : colliders)
	{
		SDL_Rect c_col = c->get_comp<Collider_component>().collider;
		if (Collision::AABB(c_col, player_col))
		{
			player.get_comp<Transform_component>().position = player_pos += (Collision::AABB_site(player_col, c_col));
			std::cout << "hit" << std::endl;
		}
		for (auto& p : projectiles)
		{
			SDL_Rect pr_col = p->get_comp<Collider_component>().collider;
			if (Collision::AABB(pr_col, c_col))
			{
				std::cout << "...Projectile hit wall..." << std::endl;
				p->destroy();
			}
		}
	}
	//projectiles collision update
	for (auto& p : projectiles)
	{
		SDL_Rect pr_col = p->get_comp<Collider_component>().collider;
		if (Collision::AABB(pr_col, skel_col))
		{
			std::cout << "...Projectile hit enemy..." << std::endl;
			p->destroy();
			if (skeleton.get_comp<Enemy_skeleton>().health > 0)
			{
				skeleton.get_comp<Enemy_skeleton>().health -= 1;
			}
			
		}
	}
	//camera update
	camera.x = player.get_comp<Transform_component>().position.x - 480+32;
	camera.y = player.get_comp<Transform_component>().position.y - 320+32;
	
	if (camera.x < 0) { camera.x = 0; }
	if (camera.y < 0) { camera.y = 0; }
	if (camera.x > camera.w) { camera.x = camera.w; }
	if (camera.y > camera.h) { camera.y = camera.h; }
}
//rendering
void Game::render()
{
	SDL_RenderClear(renderer);
	//drawing tiles
	for (auto& t : tiles)
	{
		t->draw();
	}
	//drawing colliders
	/*for (auto& c : colliders)
	{
		c->draw();
	}*/
	//drawing enemis
	for (auto& e : enemis)
	{
		e->draw();
	}
	//drawing players
	for (auto& p : players)
	{
		p->draw();
	}
	//drawing projectiles
	for (auto& pr : projectiles)
	{
		pr->draw();
	}
	
	//drawing labels
	label.draw();

	SDL_RenderPresent(renderer);
}
//cleeaning
void Game::cleen()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	std::cout << "...Game cleaned..." << std::endl;
}



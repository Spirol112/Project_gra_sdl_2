#include "Asset_manager.h"
#include"Components.h"

Asset_manager::Asset_manager(Manager* man): manager(man)
{
}

Asset_manager::~Asset_manager()
{
}

void Asset_manager::create_projectile(Vector_2D pos, Vector_2D vel,
	int range, int speed, std::string id)
{
	auto& projectile(manager->add_entity());
	projectile.add_component<Transform_component>(pos.x,pos.y,32,32,0.5);
	projectile.add_component<Sprite_component>(id,false);
	projectile.add_component <Projectile_component>(range, speed,vel);
	projectile.add_component<Collider_component>("projectile");
	projectile.add_group(Game::group_projectiles);
}

void Asset_manager::add_texture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::load_texture(path));
}

SDL_Texture* Asset_manager::get_texture(std::string id)
{
	return textures[id];
}

void Asset_manager::add_font(std::string id, std::string path, int font_size)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), font_size));
}

TTF_Font* Asset_manager::get_font(std::string id)
{
	return fonts[id];
}

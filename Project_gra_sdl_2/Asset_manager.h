#pragma once
#include<map>
#include<string>
#include"TextureManager.h"
#include"Vector_2D.h"
#include"ECS.h"
#include"SDL_ttf.h"


class Asset_manager
{
private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
public:
	Asset_manager(Manager* man);
	~Asset_manager();

	//game objects

	void create_projectile(Vector_2D pos, Vector_2D vel,int range, int speed,std::string id);

	//texture managment
	void add_texture(std::string id,const char* path);
	SDL_Texture* get_texture(std::string id);

	//fonts 
	void add_font(std::string id, std::string path, int font_size);
	TTF_Font* get_font(std::string id);

};


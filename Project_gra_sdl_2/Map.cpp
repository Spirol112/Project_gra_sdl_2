#include "Map.h"
#include "TextureManager.h"
#include"Game.h"
#include<fstream>
#include"ECS.h"
#include"Components.h"

extern Manager manager;

Map::Map(std::string t_id, int ms, int ts) : tex_ID(t_id),map_scale(ms), tile_size(ts)
{
	scaled_size = ms * ts;
}
//Map::Map(const char* p, int ms, int ts) : path(p), map_scale(ms), tile_size(ts)
//{
//	scaled_size = ms * ts;
//}
Map::~Map()
{
}

void Map::load_map(std::string path, int size_x, int size_y)
{
	char c;
	std::fstream map_file;
	map_file.open(path);

	int src_x;
	int src_y;

	for (int y = 0; y < size_y; y++)
	{
		for (int x = 0; x < size_x; x++)
		{
			map_file.get(c);
			src_y = atoi(&c) * tile_size;
			map_file.get(c);
			src_x = atoi(&c) * tile_size;
			add_tile(src_x, src_y, x * scaled_size, y * scaled_size);
			map_file.ignore();
		}
	}

	map_file.ignore();

	for (int y = 0; y < size_y; y++)
	{
		for (int x = 0; x < size_x; x++)
		{
			map_file.get(c);
			if (c == '1')
			{
				auto& t_col(manager.add_entity());
				t_col.add_component<Collider_component>("terrain", x * scaled_size, y * scaled_size, scaled_size);
				t_col.add_group(Game::group_colliders);
			}
			map_file.ignore();
		}
	}

	map_file.close();
}

void Map::add_tile(int src_x, int src_y, int xpos, int ypos)
{
	auto& tile(manager.add_entity());
	tile.add_component<Tile_component>(src_x, src_y, xpos, ypos, tile_size, map_scale, tex_ID);
	tile.add_group(Game::group_map);
}

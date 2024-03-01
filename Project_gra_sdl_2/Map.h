#pragma once
#include<string>

class Map
{
public:
	Map(std::string t_id,int ms,int ts);
	/*Map(const char* path, int ms, int ts);*/
	~Map();

	void load_map(std::string path, int size_x, int size_y);
	void add_tile(int src_x, int src_y, int xpos, int ypos);

private:
	std::string tex_ID;
	/*const char* path;*/
	int map_scale;
	int tile_size;
	int scaled_size;
};


#pragma once
#include"SDL.h"
#include "Vector_2D.h"

class Collider_component;

class Collision
{
private:

public:
	static bool AABB(const SDL_Rect& rec_a, const SDL_Rect& rec_b);
	static bool AABB(const Collider_component& col_a, const Collider_component& col_b);
	static Vector_2D AABB_site(const SDL_Rect& rec_a, const SDL_Rect& rec_b);
};


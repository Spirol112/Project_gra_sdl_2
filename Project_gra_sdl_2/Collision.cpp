#include "Collision.h"
#include"Collider_component.h"
#include<iostream>

bool Collision::AABB(const SDL_Rect& rec_a, const SDL_Rect& rec_b)
{
	if (
		rec_a.x + rec_a.w >= rec_b.x &&
		rec_b.x + rec_b.w >= rec_a.x &&
		rec_a.y + rec_a.h >= rec_b.y &&
		rec_b.y + rec_b.h >= rec_a.y
		)
	{
		return true;
	}
	else { return false; }
}

bool Collision::AABB(const Collider_component& col_a, const Collider_component& col_b)
{
	if (AABB(col_a.collider, col_b.collider))
	{
		//std::cout << col_a.tag << ">>Hit<<" << col_b.tag << std::endl;
		return true;
	}
	else { return false; }
}

Vector_2D Collision::AABB_site(const SDL_Rect& rec_a, const SDL_Rect& rec_b)
{
	Vector_2D temp_vec (0, 0);
	if (rec_a.x + rec_a.w >= rec_b.x &&
		rec_a.y + rec_a.h >= rec_b.y &&
		rec_b.y + rec_b.h >= rec_a.y&&
		rec_a.x < rec_b.x) 
	{ 
		temp_vec += Vector_2D(-1, 0);
	}
	 if (rec_b.x  <= rec_b.x+rec_b.w &&
			rec_a.y + rec_a.h >= rec_b.y &&
			rec_b.y + rec_b.h >= rec_a.y&&
			rec_b.x < rec_a.x) 
	 {
		 temp_vec += Vector_2D(1, 0); 
	 }
	if (rec_a.y + rec_a.h >= rec_b.y&&
			rec_a.x + rec_a.w >= rec_b.x &&
			rec_b.x + rec_b.w >= rec_a.x&&
			rec_a.y < rec_b.y)
	{
		temp_vec += Vector_2D(0, -1); 
	}
	if (rec_b.y + rec_b.h >= rec_a.y&&
			rec_a.x + rec_a.w >= rec_b.x &&
			rec_b.x + rec_b.w >= rec_a.x &&
			rec_b.y < rec_a.y) 
	{
		temp_vec += Vector_2D(0, 1); 
	}
	return temp_vec;

}

#pragma once
#include"ECS.h"
#include"Components.h"
#include"Vector_2D.h"

class Projectile_component :public Component
{
private:
	Transform_component* transform;

	int range{};
	int speed{};
	int distance{};
	Vector_2D velocity;

public:
	Projectile_component(int rng, int sp, Vector_2D vel) : range(rng), speed(sp), velocity(vel)
	{
	}
	~Projectile_component()
	{}

	void init()override
	{
		transform = &entity->get_comp<Transform_component>();
		transform->velocity = velocity;
	}
	void update()override
	{
		distance += speed;

		if (distance > range)
		{
			std::cout << "...Projectile out of range..." << std::endl;
			entity->destroy();
		}
		else if (transform->position.x > Game::camera.x + Game::camera.w ||
				transform->position.x<Game::camera.x||
				transform->position.y>Game::camera.y+Game::camera.h||
				transform->position.y < Game::camera.y)
		{
			std::cout << "...Projectile out of bounds..." << std::endl;
			entity->destroy();
		}
	}
};
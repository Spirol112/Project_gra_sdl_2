#pragma once
#include"Components.h"
#include"SDL.h"
#include"TextureManager.h"
#include"Vector_2D.h"

class Enemy_skeleton : public Component
{
private:
	bool is_moving{};
	int i {};
	int a{};
	int x_offset{};
public:
	Transform_component* transform;
	Sprite_component* sprite;
	int health{};

	Enemy_skeleton()
	{
		health = 10;
	}

	~Enemy_skeleton(){}

	void init()override
	{
		transform = &entity->get_comp<Transform_component>();
		sprite = &entity->get_comp<Sprite_component>();
		transform->velocity = Vector_2D(-0.5, 0);
		is_moving = true;
		i = 0;
		x_offset = 0;
		a = 0;
	}

	void update()override
	{
		if (health <= 0)
		{
			
			death();
			//std::cout << (sprite->get_src_rect().x) << "   " << ((sprite->get_src_rect().x) / sprite->get_src_rect().w) << std::endl;
			
				
				sprite->play("enemy_death");

				if (i == 0)
				{
					//sprite->set_frames(0);
					x_offset = sprite->get_src_rect().x;

					std::cout<< "offset: "<<x_offset / sprite->get_src_rect().w << std::endl;
					if (x_offset > 7)
					{
						sprite->set_src_rect_x(sprite->get_src_rect().x - x_offset);
					}
					i++;
				}

				//std::cout << (sprite->get_src_rect().x) << "   " << ((sprite->get_src_rect().x) / sprite->get_src_rect().w) << std::endl;

				if (9 <= ((sprite->get_src_rect().x) / sprite->get_src_rect().w))
				{

					sprite->set_animated(false);
				}
				
			
		}

		/*if (transform->velocity.x == 0.0f)
		{
			sprite->play("skeleton_idle");
			sprite->sprite_flip = SDL_FLIP_NONE;
		}
		else
		{
			sprite->play("skeleton_walk");
		}*/

		if (is_moving)
		{
			move();
		}
		else
		{
			transform->velocity.zero();
		}

		if (transform->velocity.x < 0)
		{
			sprite->play("enemy_walk");
			sprite->sprite_flip = SDL_FLIP_HORIZONTAL;
		}
		else if(transform->velocity.x > 0)
		{
			sprite->play("enemy_walk");
			sprite->sprite_flip = SDL_FLIP_NONE;
		}

		
		
	}
	void move()
	{
		if (transform->position.x <= 1400)
		{
			transform->velocity = Vector_2D(0.5, 0);
		}
		if (transform->position.x >= 2000)
		{
			transform->velocity = Vector_2D(-0.5, 0);
		}
	}
	void set_move(bool is_mov)
	{
		is_moving = is_mov;
	}
	void death()
	{
		is_moving = false;
		
		//if (sprite->get_feames() == (sprite->get_src_rect().x / sprite->get_src_rect().w))
		//{
		//	if (i == 0)
		//	{
		//		//sprite->set_frames(0);
		//		
		//		i++;
		//	}
		//	
		//}
		
		
		
	}
};
class Fire_enemy_skeleton : public Component
{
private:
	bool is_moving{};

public:
	Transform_component* transform;
	Sprite_component* sprite;
	int health{};

	Fire_enemy_skeleton()
	{
		health = 10;
	}

	~Fire_enemy_skeleton() {}

	void init()override
	{
		transform = &entity->get_comp<Transform_component>();
		sprite = &entity->get_comp<Sprite_component>();
		transform->velocity = Vector_2D(-0.5, 0);
		is_moving = true;

	}

	void update()override
	{
		if (health == 0)
		{
			death();
		}
		/*if (transform->velocity.x == 0.0f)
		{
			sprite->play("skeleton_idle");
			sprite->sprite_flip = SDL_FLIP_NONE;
		}
		else
		{
			sprite->play("skeleton_walk");
		}*/

		if (is_moving)
		{
			move();
		}
		else
		{
			transform->velocity.zero();
		}

		if (transform->velocity.x < 0)
		{
			sprite->play("skeleton_walk");
			sprite->sprite_flip = SDL_FLIP_HORIZONTAL;
		}
		else if (transform->velocity.x > 0)
		{
			sprite->play("skeleton_walk");
			sprite->sprite_flip = SDL_FLIP_NONE;
		}



	}
	void move()
	{
		if (transform->position.x <= 1800)
		{
			transform->velocity = Vector_2D(0.5, 0);
		}
		if (transform->position.x >= 2400)
		{
			transform->velocity = Vector_2D(-0.5, 0);
		}
	}
	void set_move(bool is_mov)
	{
		is_moving = is_mov;
	}
	void death()
	{
		is_moving = false;
		sprite->play("skeleton_death");
		sprite->set_animated(false);
	}
};
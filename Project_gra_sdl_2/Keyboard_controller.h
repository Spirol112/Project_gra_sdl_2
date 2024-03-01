#pragma once
#include"Game.h"
#include"ECS.h"
#include"Components.h"
#include<cmath>

class Keyboard_controller :public Component
{
private:
	Vector_2D pos;
	Vector_2D vel;
	Vector_2D mouse_pos;

	int m_x;
	int m_y;
	bool reload;
public:
	Transform_component* transform;
	Sprite_component* sprite;

	void init()override
	{
		transform = &entity->get_comp<Transform_component>();
		sprite = &entity->get_comp<Sprite_component>();

		reload = true;
		m_x = m_y = 0;
	}

	void update()override
	{
		pos = transform->position;
		vel = transform->velocity;

		Vector_2D p_pos_scr((pos.x - Game::camera.x+32), (pos.y - Game::camera.y+32));
		float p_x{};
		float p_y{};
		float l_p{};
		//mause update
		if (Game::event.type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&m_x, &m_y);
			mouse_pos = Vector_2D(m_x, m_y);
			mouse_pos -= p_pos_scr;
		}
		
		//projectile velocity vector
		p_x = (mouse_pos.x / 96);
		p_y = (mouse_pos.y / 64);

		//normalisation projectile speed
		l_p = sqrt(((p_x) * (p_x)) + ((p_y ) * (p_y )));

		//std::cout <<mouse_pos.x<<":"<<mouse_pos.y<<"-> "<< l_p << std::endl;

		float diference_length = 4 / l_p;
		p_x = p_x * diference_length;
		p_y = p_y * diference_length;
		
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->play("walk_up");
				sprite->sprite_flip = SDL_FLIP_NONE;
					break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->play("walk_down");
				sprite->sprite_flip = SDL_FLIP_NONE;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->play("walk");
				sprite->sprite_flip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->play("walk");
				sprite->sprite_flip = SDL_FLIP_NONE;
				break;
			case SDLK_SPACE:
				/*if (reload)
				{
					Game::assets->create_projectile((pos += Vector_2D(32, 32))
						, Vector_2D(p_x,p_y),
						200, 2, "projectile");
					reload = false;
				}*/
				break;
			case SDLK_r:
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->play("idle");
				sprite->sprite_flip = SDL_FLIP_NONE;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->play("idle");
				sprite->sprite_flip = SDL_FLIP_NONE;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->play("idle_site");
				sprite->sprite_flip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->play("idle_site");
				sprite->sprite_flip = SDL_FLIP_NONE;
				break;
			case SDLK_SPACE:
				//reload = true;
				break;
			case SDLK_ESCAPE:
				Game::is_running = false;
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (reload)
			{
				Game::assets->create_projectile((pos += Vector_2D(32, 32))
					, Vector_2D(p_x, p_y),
					200, 2, "projectile");
				reload = false;
			}
		}
		if (Game::event.type == SDL_MOUSEBUTTONUP)
		{
			reload = true;
		}
	}
};

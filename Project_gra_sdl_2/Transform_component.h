#pragma once
#include"Components.h"
#include"Vector_2D.h"

class Transform_component : public Component
{
private:

public:
	Vector_2D position;
	Vector_2D velocity;

	int height = 32;
	int width = 32;
	float scale = 1;

	int speed = 3;

	Transform_component()
	{
		position.zero();
	}

	Transform_component(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	Transform_component(int s)
	{
		position.zero();
		scale = s;
	}

	Transform_component(float x, float y,int h,int w, float s)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}

	void init() override
	{
		velocity.zero();
	}

	void update()override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};


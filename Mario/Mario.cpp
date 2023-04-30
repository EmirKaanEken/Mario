#include "Mario.h"

Mario::Mario(RenderWindow* window) : Object(window) {
	
	char path[64];
	
	for (int i = 0; i < 7; i++) {
		sprintf(path, "../assets/mario%d.png", i + 1);
		this->textures[i].loadFromFile(path);
	}

	this->textures[7].loadFromFile("../assets/mariohead.png");
	this->sprite.setTexture(this->textures[0]);
	this->sprite.setOrigin(Vector2f(this->sprite.getTextureRect().width / 2.0f, this->sprite.getTextureRect().height / 2.0f));
	//this->sprite.setScale(-1, 1);

	this->state = 0;
	this->footState = 0;
	this->vx = 12;
	this->vy = 0;
}

void Mario::move(moveDirection dir, bool isOnFloor)
{
	switch (this->state)
	{
	case 0:
		if (LEFT == dir)
		{
			if (heading == 2)
			{
				this->sprite.setScale(1, 1);
				this->heading = 1;
			}
			sprite.move(Vector2f(-vx, 0));
			state = 1;
		}
		else if (RIGHT == dir)
		{
			if (heading == 0 || heading == 1)
			{
				this->sprite.setScale(-1, 1);
				this->heading = 2;
			}
			sprite.move(Vector2f(vx, 0));
			state = 1;
		}
		if (!isOnFloor)
			state = 5;
		break;
	case 1:
		footState = 0;
		if (LEFT == dir)
		{
			if (heading == 2)
			{
				this->sprite.setScale(1, 1);
				this->heading = 1;
			}
			sprite.move(Vector2f(-vx, 0));
			state = 2;
		}
		else if (RIGHT == dir)
		{
			if (heading == 0 || heading == 1)
			{
				this->sprite.setScale(-1, 1);
				this->heading = 2;
			}
			sprite.move(Vector2f(vx, 0));
			state = 2;
		}
		else if (STAND == dir)
		{
			state = 0;
		}
		if (!isOnFloor)
			state = 5;
			break;
	case 2:
		if (LEFT == dir)
		{
			if (heading == 2)
			{
				this->sprite.setScale(1, 1);
				this->heading = 1;
			}
			sprite.move(Vector2f(-vx, 0));
			if (footState)
				state = 1;
			else
				state = 3;
		}
		else if (RIGHT == dir)
		{
			if (heading == 0 || heading == 1)
			{
				this->sprite.setScale(-1, 1);
				this->heading = 2;
			}
			sprite.move(Vector2f(vx, 0));
			if (footState)
				state = 1;
			else
				state = 3;
		}
		else if (STAND == dir)
		{
			state = 0;
		}
		if (!isOnFloor)
			state = 5;
		break;
	case 3:
		footState = 1;
		if (LEFT == dir)
		{
			if (heading == 2)
			{
				this->sprite.setScale(1, 1);
				this->heading = 1;
			}
			sprite.move(Vector2f(-vx, 0));
			state = 2;
		}
		else if (RIGHT == dir)
		{
			if (heading == 0 || heading == 1)
			{
				this->sprite.setScale(-1, 1);
				this->heading = 2;
			}
			sprite.move(Vector2f(vx, 0));
			state = 2;
		}
		else if (STAND == dir)
		{
			state = 0;
		}
		if (!isOnFloor)
			state = 5;
		break;
	case 4:

		break;
	case 5:
		if (LEFT == dir)
		{
			if (heading == 2)
			{
				this->sprite.setScale(1, 1);
				this->heading = 1;
			}
			sprite.move(Vector2f(-vx, 0));
			state = 2;
		}
		else if (RIGHT == dir)
		{
			if (heading == 0 || heading == 1)
			{
				this->sprite.setScale(-1, 1);
				this->heading = 2;
			}
			sprite.move(Vector2f(vx, 0));
			state = 2;
		}
		else if (STAND == dir)
		{
			state = 0;
		}
		if (!isOnFloor)
			state = 5;
		break;
	case 6:

		break;
	case 7:

		break;
	default:
		break;
	}
	sprite.setTexture(textures[state]);
}

void Mario::jump(bool down, bool up)
{
	if (down)
	{
		vy = 0;
		if (up)
			vy = -20;
	}
	else {
		vy += 11 * 0.1;
	}
	sprite.move(Vector2f(0, vy));
}
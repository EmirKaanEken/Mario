#include "Turtle.h"

Turtle::Turtle(RenderWindow* window) : Object(window) {
	
	char path[64];
	
	for (int i = 0; i < 5; i++) {
		sprintf(path, "../assets/turtle%d.png", i + 1);
		this->textures[i].loadFromFile(path);
	}

	this->sprite.setTexture(this->textures[1]);
	this->sprite.setOrigin(Vector2f(this->sprite.getTextureRect().width / 2.0f, this->sprite.getTextureRect().height / 2.0f));

	this->vx = 0;
	this->vy = 0;
}

void Turtle::move()
{
	if (1 == this->heading)
	{
		if (this->boundingBox().left <= 0) {
			this->heading = 2;
			vx = 12;
			this->sprite.setScale(1, 1);
		}
		else if (this->boundingBox().top >= 725 && this->boundingBox().left <= 160)
		{
			this->sprite.setPosition(800, 80);
		}
		else
			vx = -12;
	}
	else
	{
		if (this->boundingBox().left + this->boundingBox().width >= WINDOW_WIDTH)
		{
			this->heading = 1;
			vx = -12;
			this->sprite.setScale(-1, 1);
		}
		else if (this->boundingBox().top >= 725 && this->boundingBox().left >= (WINDOW_WIDTH - 160))
		{
			this->sprite.setPosition(200, 80);
		}
		else
			vx = 12;
	}
	switch (state)
	{
	case 0:
		footState = false;
		state = 1;
		if (this->getIsDead())
			state = 4;
		break;
	case 1:
		if (footState)
			state = 0;
		else
			state = 2;
		if (this->getIsDead())
			state = 4;
		break;
	case 2:
		footState = true;
		state = 1;
		if (this->getIsDead())
			state = 4;
		break;
	case 3:
		break;
	case 4:
			state = 4;
			this->vx = 0;
			this->canKill = false;
		break;
	default:
		break;
	}
	this->sprite.move(vx, vy);
	this->sprite.setTexture(textures[state]);
}

void Turtle::jump(bool down)
{
	if (down)
	{
		vy = 0;
	}
	else {
		vy += 11 * 0.1;
	}
	sprite.move(Vector2f(0, vy));
}
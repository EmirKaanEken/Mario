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
		vx = -12;
	else
		vx = 12;
	this->sprite.move(vx, vy);
}
#include "Turtle.h"

Turtle::Turtle(RenderWindow* window) : Object(window) {
	
	char path[64];
	
	for (int i = 0; i < 5; i++) {
		sprintf(path, "../assets/turtle%d.png", i + 1);
		this->textures[i].loadFromFile(path);
	}

	this->sprite.setTexture(this->textures[1]);

	this->vx = 0;
	this->vy = 0;
}
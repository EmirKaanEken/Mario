#include "Mario.h"

Mario::Mario(RenderWindow* window) : Object(window) {
	
	char path[64];
	
	for (int i = 0; i < 7; i++) {
		sprintf(path, "../assets/mario%d.png", i + 1);
		this->textures[i].loadFromFile(path);
	}

	this->textures[7].loadFromFile("../assets/mariohead.png");
	this->sprite.setTexture(this->textures[0]);

	this->vx = 0;
	this->vy = 0;
}
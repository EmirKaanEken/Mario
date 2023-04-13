#pragma once
#include "Common.h"
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"

class Game {
	Mario* mario;		//þimdilik mario ve turtle ayrý ama, bu ikisi obje listesinde bir arada duracak ve oradan ulaþýcaz.
	Turtle* turtles;
	RenderWindow* window;
	Sprite ground;
	Texture groundTexture;
	Sprite bricks[76];
	Texture brickTexture;
	Sprite lowerPipes[2];
	Texture lowerPipeTexture;
	Sprite upperPipes[2];
	Texture upperPipeTexture;
public:
	Game();
	//~Game();
	void drawBackground(RenderWindow& window);
	//bool onFloor(Object* obj);
	//bool checkCollision(Turtle* t, Mario* m, int& side);
	void update(void);
};
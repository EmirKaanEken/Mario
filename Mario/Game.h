#pragma once
#include "Common.h"
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"

class Game {
	Mario* mario;		//þimdilik mario ve turtle ayrý ama, bu ikisi obje listesinde bir arada duracak ve oradan ulaþýcaz.
	Object* objects;
	RenderWindow* window;
	Texture bgTextures[4];
	Sprite* platforms;
public:
	Game();
	//~Game();
	void drawBackground(RenderWindow& window);
	void setBackground(RenderWindow& window);
	Turtle* addTurtle(void);
	//bool onFloor(Object* obj);
	//bool checkCollision(Turtle* t, Mario* m, int& side);
	void update(void);
};
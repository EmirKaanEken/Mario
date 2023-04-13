#pragma once
#include "Common.h"
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"

class Game {
	Mario* mario;		//�imdilik mario ve turtle ayr� ama, bu ikisi obje listesinde bir arada duracak ve oradan ula��caz.
	Turtle* turtles;
	RenderWindow* window;
public:
	Game();
	//~Game();
	//void drawBackground(RenderWindow& window);
	//bool onFloor(Object* obj);
	//bool checkCollision(Turtle* t, Mario* m, int& side);
	void update(void);
};
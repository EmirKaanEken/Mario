#pragma once
#include "Common.h"
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"

class Game {
	Mario* mario;		//�imdilik mario ve turtle ayr� ama, bu ikisi obje listesinde bir arada duracak ve oradan ula��caz.
	Object* objects;
	RenderWindow* window;
	Texture bgTextures[4];
	Sprite* platforms;
	bool isUpPressed, isRightPressed, isLeftPressed;
public:
	Game();
	//~Game();
	void drawBackground(RenderWindow& window);
	void setBackground(RenderWindow& window);
	Turtle* addTurtle(void);
	void handleKeyPres(Event&);
	void handleKeyRelease(Event&);
	void handleMarioMove(void);
	bool onFloor(Object* obj);
	//bool checkCollision(Turtle* t, Mario* m, int& side);
	void update(void);
};
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
	bool isUpPressed, isRightPressed, isLeftPressed;
	float timePassed;
public:
	Game();
	//~Game();
	void drawBackground(RenderWindow& window);
	void setBackground(RenderWindow& window);
	Turtle* addTurtle(void);
	Mario* addMario(void);
	void spawnTurtle(void);
	void handleKeyPres(Event&);
	void handleKeyRelease(Event&);
	void handleMarioMove(void);
	void handleTurtleMove(Object*);
	bool onFloor(Object* obj);
	bool checkCollusion(Turtle*, Mario*, int&);
	void drawObjects(void);
	void moveObjects(void);
	void update(void);
};
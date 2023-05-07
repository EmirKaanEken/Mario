#pragma once
#include "Common.h"
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"
#include "ScoreBoard.h"

class Game {
	Mario* mario;
	Object* objects;		//this linked list stores turtles and our mario object
	RenderWindow* window;
	Texture bgTextures[4];
	Sprite* platforms;		//platform array, contains bricks, floor and pipes
	Font font;
	Text text[2];
	bool isUpPressed, isRightPressed, isLeftPressed;		//used in key events
	float timePassed;										
public:
	Game();
	//~Game();
	ScoreBoard *scoreBoard;
	int gameState;		//0: Main page		1: In game		2: Win Page		3: Lose Page
	void drawBackground(RenderWindow& window);
	void setBackground();
	void setMainScreen();
	void drawMainScreen(RenderWindow& window);
	Turtle* addTurtle(void);
	Mario* addMario(void);
	void removeObject(Object*);
	void handleDeadTurtle(void);
	void handleMarioDie(void);
	void handleTurtleDie(Object*);
	void spawnTurtle(void);
	void handleKeyPres(Event&);
	void handleKeyRelease(Event&);
	void handleMarioMove(void);
	void handleTurtleMove(Object*);
	bool onFloor(Object* obj);
	bool checkCollusion(Turtle*, Mario*, int&);
	void handleCollusion(void);
	void drawObjects(void);
	void moveObjects(void);
	void update(void);
	void checkAndHandleTurtleMeet(void);
};
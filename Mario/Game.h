#pragma once
#include "Common.h"
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"
#include "ScoreBoard.h"

class Game {
	Mario* mario;
	Object* objects;
	RenderWindow* window;
	Texture bgTextures[4];
	Sprite* platforms;
	Font font;
	Text text[2];
	bool isUpPressed, isRightPressed, isLeftPressed;
	float timePassed;
public:
	Game();
	//~Game();
	ScoreBoard *scoreBoard;
	int gameState;		//0: ana ekran		1: oyunda		2: win			3: lose
	void drawBackground(RenderWindow& window);
	void setBackground();
	void setMainScreen();
	void drawMainScreen(RenderWindow& window);
	Turtle* addTurtle(void);
	Mario* addMario(void);
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
};
#pragma once
#include "Common.h"
#include "Object.h"

class Turtle : public Object {
	float vx;
	float vy;
public:
	Turtle(RenderWindow* window);
	void move();
	void jump(bool down);
	void fall(void);
	int surpriseCounter;
};
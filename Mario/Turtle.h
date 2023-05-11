#pragma once
#include "Common.h"
#include "Object.h"

class Turtle : public Object {
	float vx;
	float vy;
	float dvx;
	bool isHalfDead;
	bool canDie;
	bool isTriggered;
public:
	Turtle(RenderWindow* window);
	void move();
	void jump(bool down);
	void fall(void);
	void setVerticalSpeed(float s) { this->vy = s; }
	void setIsHalfDead(bool halfDead) { this->isHalfDead = halfDead; }
	bool getIsHalfDead(void) { return this->isHalfDead; }
	bool getCanDie(void) { return this->canDie; }
	void setExtraSpeed(float s) { this->dvx = s;}
};
#pragma once
#include "Common.h"
#include "Object.h"

class Mario : public Object {
	float vx;
	float vy;
public:
	Mario(RenderWindow* window);
	//void move();
	//void jump(bool down);
	//void fall(void);
};

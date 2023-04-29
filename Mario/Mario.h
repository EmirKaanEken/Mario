#pragma once
#include "Common.h"
#include "Object.h"

class Mario : public Object {
	float vx;
	float vy;
public:
	Mario(RenderWindow* window);
	enum moveDirection {
		UP,
		RIGHT,
		LEFT
	};
	void move(moveDirection);
	void jump(bool, bool);
	//void fall(void);
	void setVerticalSpeed(float s) { this->vy = s; }
	float getVerticalSpeed(void) { return this->vy; }
};

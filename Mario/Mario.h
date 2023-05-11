#pragma once
#include "Common.h"
#include "Object.h"

class Mario : public Object {
	float vx;
	float vy;
	bool isOnFloorPrevCycle;
public:
	Mario(RenderWindow* window);
	enum moveDirection {		//this enum not only has directions but also STAND and DEAD, since they are also different states of moves to be processed
		RIGHT,
		LEFT,
		STAND,
		DEAD
	};
	void move(moveDirection, bool);
	void jump(bool, bool);
	void fall(void);
	void setVerticalSpeed(float s) { this->vy = s; }
	float getVerticalSpeed(void) { return this->vy; }
	Texture getLiveTexture(void) { return this->textures[7]; }	//returns mario head texture
};

#pragma once
#include "Common.h"

class Object {
protected:
	Texture textures[8];
	Sprite sprite;
	RenderWindow* window;
	int state;
	int footState;
	int heading;		//0: beggining of the game		1: To left		2: To right
	bool isdead;		
	Object* next;		//to be able to make linked list of this object
	friend class Game;	//Game class able to access this class's members. 
	bool canKill;		//When an object is dead, it should not be able to kill while performing death animation.
public:
	Object(RenderWindow* window);
	void setPosition(Vector2f);
	Vector2f getPosition();
	IntRect boundingBox(void);		
	void draw(RenderWindow& window);
	void setAsDead(void) { this->isdead = true; }
	void setAsLive(void) { this->isdead = false; }
	bool getIsDead(void) { return this->isdead; }
	/*virtual functions, will behave different for turtles and mario during the run-time*/
	virtual void move(void){}
	virtual void fall(void){}
	virtual void jump(bool down){}
};

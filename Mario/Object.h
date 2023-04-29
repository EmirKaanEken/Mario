#pragma once
#include "Common.h"

class Object {
	Vector2f pos;
protected:
	Texture textures[8];
	Sprite sprite;
	RenderWindow* window;
	int state;
	int footState;
	int heading;
	Object* next;
	friend class Game;
	//friend class ObjectList;
public:
	Object(RenderWindow* window);
	void setPosition(Vector2f);
	Vector2f getPosition();
	IntRect boundingBox(void);
	void draw(RenderWindow& window);
	virtual void move(void){}
	virtual void fall(void){}
	virtual void jump(bool down){}
};

/*class ObjectList {
	Object* head, * tail;
public:
	ObjectList();
};*/

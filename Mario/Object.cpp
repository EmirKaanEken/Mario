#include "Object.h"

Object::Object(RenderWindow* window)
{
	this->window = window;
	this->state = 0;
	this->heading = 0;
	this->next = NULL;
	this->prev = NULL;
}

void Object::setPosition(Vector2f pos)
{
	this->pos = pos;
	sprite.setPosition(pos);
}

void Object::draw(RenderWindow& window)
{
	window.draw(sprite);
}

Vector2f Object::getPosition()
{
	return this->pos;
}
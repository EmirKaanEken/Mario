#include "Object.h"

Object::Object(RenderWindow* window)
{
	this->window = window;
	this->state = 0;
	this->heading = 0;
	this->next = NULL;
	this->canKill = true;
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
	return this->sprite.getPosition();
}

IntRect Object::boundingBox(void)
{
	return static_cast<IntRect>(this->sprite.getGlobalBounds());
}
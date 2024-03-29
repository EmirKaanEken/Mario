#include "Turtle.h"

Turtle::Turtle(RenderWindow* window) : Object(window) {
	
	char path[64];
	
	for (int i = 0; i < 5; i++) {
		sprintf(path, "../assets/turtle%d.png", i + 1);
		this->textures[i].loadFromFile(path);
	}
	/*all turtle textures stored inside the created turtle object as Texture array*/

	this->sprite.setTexture(this->textures[1]);
	this->sprite.setOrigin(Vector2f(this->sprite.getTextureRect().width / 2.0f, this->sprite.getTextureRect().height / 2.0f));
	/*turtle started with one of its walking states. Also its origin is set to center of the bounding box in order to provide a proper left-right heading later*/

	this->vx = 0;
	this->vy = 0;
	this->dvx = 0;
	this->animationTimeCounter = 0;
	this->isTriggered = false;
}

void Turtle::move()
{
	if (1 == this->heading)	//if it moving to left
	{
		this->sprite.setScale(-1, 1);
		if (this->boundingBox().left <= 0) {	//if it hit the leftmost of the screen, start to move to right, change heading to 2(right) and setScale to make texture heading right
			this->heading = 2;
			this->sprite.setScale(1, 1);
			if (isTriggered)				//if a turtle once triggered, it will directly go it max speed it can reach
				vx = 17;
			else
				vx = 12 + dvx;
		}
		else if (this->boundingBox().top >= 725 && this->boundingBox().left <= 160)	//if it gose into the pipes at the floor, they out of the pipes above and opposite side
		{																			// since it moving left right now, it goes into the left one, teleport to the upper right
			this->sprite.setPosition(800, 80);
		}
		else			//if it do not hit the leftmost screen or go inside a pipe, just continue to move to left
			if (isTriggered)
				vx = -17;
			else
				vx = -12 - dvx;
	}
	else		//if it moving to right
	{
		this->sprite.setScale(1, 1);
		if (this->boundingBox().left + this->boundingBox().width >= WINDOW_WIDTH)	//if it hit the rightmost of the screen, start to move to left, change heading to 1(left) and setScale to make texture heading left
		{
			this->heading = 1;
			this->sprite.setScale(-1, 1);
			if (isTriggered)
				vx = -17;
			else
				vx = -12 - dvx;
		}
		else if (this->boundingBox().top >= 725 && this->boundingBox().left >= (WINDOW_WIDTH - 160)) //if it gose into the pipes at the floor, they out of the pipes above and opposite side
		{																							 // since it moving right right now, it goes into the right one, teleport to the upper left
			this->sprite.setPosition(200, 80);
		}
		else		//if it do not hit the rightmost screen or go inside a pipe, just continue to move to right
			if (isTriggered)
				vx = 17;
			else
				vx = 12 + dvx;
	}
	switch (state)
	{
	/*while walking, the states changes such as 0-1-2-1-0-1... At every state, it checks wheter the turtle is dead. And if it is, it jump to state 4 and never turns back */
	case 0:
		footState = false;
		state = 1;
		if (this->getIsDead())
			state = 4;
		break;
	case 1:
		if (footState)		//footstate decides direction of the state flow at the state 1. To the state 0 or state 2.
			state = 0;
		else
			state = 2;
		if (this->getIsDead())
			state = 4;
		break;
	case 2:
		footState = true;
		state = 1;
		if (this->getIsDead())
			state = 4;
		break;
	case 3:
		/*since window refresh rate is 100ms, so is frequency of this function is called. So this if structure provide 0.5 second for turtles to surprise and stay still.
		Then they will continue to walk other directions from state 1. Change of directions and coming to the state 3 are handled by "checkAndHandleTurtleMeet" function in Game class*/
		if (animationTimeCounter <= 5)
		{
			state = 3;
			vx = 0;
			animationTimeCounter++;
		}
		else
		{
			state = 1;
			animationTimeCounter = 0;
		}
		break;
	case 4:				// when a turtle die or half die, its horizontal speed is set to 0. Also it cannot kill at these states.
			state = 4;
			this->vx = 0;
			this->canKill = false;
			if (this->getIsHalfDead())		//if it half die, it wait 8 seconds to turn back to normal.
			{
				if (animationTimeCounter <= 80)
				{
					this->isTriggered = true;			
					if (animationTimeCounter <= 20)		//when it is set as half dead, we give it 2 seconds before it can be killed by sides, to prevent 
						this->canDie = false;			//	it is killed by the mario just after it is hit from below.
					else
						this->canDie = true;
					animationTimeCounter++;
				}
				else
				{
					animationTimeCounter = 0;
					state = 1;
					this->setIsHalfDead(false);
					this->canKill = true;
				}
			}
		break;
	default:
		break;
	}
	this->sprite.move(vx, 0);
	this->sprite.setTexture(textures[state]);
}

void Turtle::jump(bool down)
{
	/*"down" variable say wheter the turtle is on a floor. If it is not on a floor, that means it jump down to cliff and should be accelerated towerds to down. */
	if (down)
	{
		vy = 0;
	}
	else {
		vy += 11 * 0.1;
	}
	sprite.move(Vector2f(0, vy));
}

void Turtle::fall(void)
{
	this->state = 4;
	this->jump(false);
}
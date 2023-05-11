#include "Mario.h"

Mario::Mario(RenderWindow* window) : Object(window) {
	
	char path[64];
	
	for (int i = 0; i < 7; i++) {
		sprintf(path, "../assets/mario%d.png", i + 1);
		this->textures[i].loadFromFile(path);
	}
	this->textures[7].loadFromFile("../assets/mariohead.png");
	/*all mario textures stored inside the created Mario object as Texture array*/


	this->sprite.setTexture(this->textures[0]);
	this->sprite.setOrigin(Vector2f(this->sprite.getTextureRect().width / 2.0f, this->sprite.getTextureRect().height / 2.0f));
	/*mario started with its stand still state. Also its origin is set to center of the bounding box in order to provide a proper left-right heading texture later*/



	this->vx = 0;		
	this->vy = 0;
	this->animationTimeCounter = 0;
}

void Mario::move(moveDirection dir, bool isOnFloor)		//dir: left, right, stand and also dead state		isOnFloor: whether mario is on the floor
{
	/*since physical horizontal move of mario is independent from states, it is decided outside of the switch case block. It basically:
	if LEFT, move left and if RIGHT, move right. However, if the heading is the opposite of the inserted direction, proper scale setting should be done to the 
	texture of mario to make heading correct way. Also, while it on the floor, it checks couple of things to perform a slide effect. 
	- if LEFT or RIGHT is pressed when it just touch to ground
	- if it change direction while on the ground and not from STAND position
	it will slide.*/
	if (LEFT == dir)
	{
		if (!isOnFloorPrevCycle && isOnFloor)
			state = 4;
		if (heading == 2)
		{
			if (!(fabs(this->vx) < 0.1) && isOnFloor)
			{
				state = 4;
				if (animationTimeCounter > 1)
				{
					this->sprite.setScale(1, 1);
					this->heading = 1;
				}
			}
			else
			{
				this->sprite.setScale(1, 1);
				this->heading = 1;
			}
			
		}
		if(1 == this->heading)
			this->vx = -12;
	}
	else if (RIGHT == dir)
	{
		if (!isOnFloorPrevCycle && isOnFloor)
			state = 4;
		if (heading == 1)
		{
			if (!(fabs(this->vx) < 0.1) && isOnFloor)
			{
				state = 4;
				if (animationTimeCounter > 1)
				{
					this->sprite.setScale(-1, 1);
					this->heading = 2;
				}
			}
			else
			{
				this->sprite.setScale(-1, 1);
				this->heading = 2;
			}
			
		}
		if(2 == this->heading)
			this->vx = 12;
	}
	else if (STAND == dir || DEAD == dir)
	{
		if (STAND == dir)
		{
			if (!(fabs(this->vx) < 0.1) && isOnFloor)
			{
				state = 4;
			}
		}
		if (4 != state)
			this->vx = 0;
		else if(animationTimeCounter > 1)
			this->vx = 0;
	}
	
	sprite.move(Vector2f(vx, 0));

	switch (this->state)	//other than !onFloor, DEAD and STAND situations, states goes as 1-2-3-2-1-2... Variable "footstate" decides whether state goes from 2 to 1 or 3.
	{
	/*For all cases, if the function is called with DEAD parameter, state directly goes to 6 and process dead routine. if it not DEAD but mario is not on the floor,
	then directly goes to state 5 since mario should always stay in texture mario6 while it is on the air*/
	case 0:
		if (DEAD == dir)
		{
			state = 6;
		}
		else
		{
			if (LEFT == dir || RIGHT == dir)	//when start moving from stand still, start with state 1
			{
				state = 1;
			}
			if (!isOnFloor)
				state = 5;
		}
		break;
	case 1:
		if (DEAD == dir)
		{
			state = 6;
		}
		else
		{
			footState = 0;
			if (LEFT == dir || RIGHT == dir)
			{
				state = 2;
			}
			else if (STAND == dir)
			{
				state = 0;
			}
			if (!isOnFloor)
				state = 5;
		}
			break;
	case 2:
		if (DEAD == dir)
		{
			state = 6;
		}
		else
		{
			if (LEFT == dir || RIGHT == dir)
			{
				if (footState)
					state = 1;
				else
					state = 3;
			}
			else if (STAND == dir)
			{
				state = 0;
			}
			if (!isOnFloor)
				state = 5;
		}
		break;
	case 3:
		if (DEAD == dir)
		{
			state = 6;
		}
		else
		{
			footState = 1;
			if (LEFT == dir || RIGHT == dir)
			{
				state = 2;
			}
			else if (STAND == dir)
			{
				state = 0;
			}
			if (!isOnFloor)
				state = 5;
		}
		break;
	case 4:
		if (DEAD == dir)		// it still can die while sliding
		{
			state = 6;
		}
		else
		{
			if (animationTimeCounter <= 2)	//since refresh rate is 100ms, it will slide for 0.2 second, then continue from state 1
			{
				animationTimeCounter++;
			}
			else
			{
				animationTimeCounter = 0;
				state = 1;
			}
		}
		break;
	case 5:
		if (DEAD == dir)
		{
			state = 6;
		}
		else
		{
			if (LEFT == dir || RIGHT == dir)
			{
				state = 2;
			}
			else if (STAND == dir)
			{
				state = 0;
			}
			if (!isOnFloor)
				state = 5;
		}
		break;
	case 6:
		if (this->getIsDead())		//at every screen update, wheter the mario is still die is checked. As long as it is dead, death routine continues, else: turn back to STAND
		{													//(mario respawn is triggered on game class, when mario fall below the border of the window)
			state = 6;
			this->canKill = false;
		}
		else
		{
			state = 0;
			this->canKill = true;
		}
		break;
	default:
		break;
	}
	sprite.setTexture(textures[state]);
	/*Whether Mario was on the ground in the previous cycle is saved to check if it just landed.*/
	if (isOnFloor)
		this->isOnFloorPrevCycle = true;
	else
		this->isOnFloorPrevCycle = false;
}

void Mario::jump(bool down, bool up)
{
	/*the "down" variable represents whether mario is on the floor. the "up" variable on the other hand represents whether the key UP is pressed. With the following nested if
	structure, the jump can only be triggered while mario is on the floor. And as long is it is not on the floor, it accelerates towards to down.*/
	if (down)
	{
		vy = 0;
		if (up)
			vy = -20;
	}
	else {
		vy += 11 * 0.1;
	}
	sprite.move(Vector2f(0, vy));
}

void Mario::fall(void)
{
	this->move(Mario::moveDirection::DEAD, false);	//For the texture, it send DEAD enum. The second parameter is unimportant here due to first parameter being DEAD is already suppresses it
	this->jump(false, true);	//In sake of mario pass through the platforms, first parameter is sent as false statically. Second parameter is unimportant here also.

	/*when mario fall below the bottom border of the screen, it respawns.*/
	if (this->boundingBox().top > WINDOW_HEIGHT + 50)
	{
		this->setAsLive();
		this->setPosition(Vector2f(512, 600));
	}
}
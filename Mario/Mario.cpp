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
	/*mario started with its stand still state. Also its origin is set to center of the bounding box in order to provide a proper left-right heading later*/



	this->vx = 12;		//Mario horizontal speed. The program just multiplies it with (-1) in case of direction change but not gives it a value. So it should be initiated with a positive value
	this->vy = 0;
}

void Mario::move(moveDirection dir, bool isOnFloor)		//dir: left, right, up, stand and also dead state		isOnFloor: wheter mario is on the floor
{
	/*since horizontal move of mario is physically independent from states, it is decided outside of the switch case block. It basically:
		if LEFT, move left and if RIGHT, move right. However, if the heading is the opposite of the inserted direction, proper scale setting should be done to the texture
		to mario to heading correct way. */
	if (LEFT == dir)
	{
		if (heading == 2)
		{
			this->sprite.setScale(1, 1);
			this->heading = 1;
		}
		sprite.move(Vector2f(-vx, 0));
	}
	else if (RIGHT == dir)
	{
		if (heading == 0 || heading == 1)
		{
			this->sprite.setScale(-1, 1);
			this->heading = 2;
		}
		sprite.move(Vector2f(vx, 0));
	}
	


	switch (this->state)
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
			if (LEFT == dir)
			{
				state = 1;
			}
			else if (RIGHT == dir)
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
		if (this->getIsDead())
		{
			state = 6;
			this->canKill = false;
		}
		else
		{
			state = 0;
			this->canKill = true;
		}
		break;
	case 7:

		break;
	default:
		break;
	}
	sprite.setTexture(textures[state]);
}

void Mario::jump(bool down, bool up)
{
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
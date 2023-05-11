#include "Game.h"

Game::Game() {
	this->isLeftPressed = false;
	this->isRightPressed = false;
	this->isUpPressed = false;
	this->timePassed = 0;
	/*all keyPress variables set 0, no key is pressed at the beggining. The game time is 0.*/
	
	window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");

	this->setBackground();		//static coordinates of the platforms are set

	mario = addMario();		//created a mario object and is added to Object linked list. It can be directly accessible with mario variable inside the Game class, without a travel on the linked list  
	mario->setPosition(Vector2f(512, 756));	//static beginning coordinates

	scoreBoard = new ScoreBoard(mario->getLiveTexture());

	font.loadFromFile("../assets/font.ttf");
	for (int i = 0; i < 2; i++)
	{
		text[i].setFont(font);
		text[i].setFillColor(Color::Magenta);
	}
	text[0].setCharacterSize(120);
	/*The font is initialized in sake of using it at the main page, win page and lose page*/
	

	gameState = 0;		//initial game state is 0(main page).
}

void Game::update(void) {
	while (window->isOpen())	//As long as window is open...
	{
		Event event;

		window->clear();

		if (0 == gameState)	//handles displaying main page. It resets all the game variables.
		{
			scoreBoard->setLives(3);
			scoreBoard->setScore(0);

		
			Object* cur = objects;
			while (cur)
			{
				if (dynamic_cast<Mario*>(cur) == NULL)
				{
					removeObject(cur);
					cur = objects;		//since the cur is deleted at the previous line, we define it as objects once again. When there left only the mario, the loop cyles just one more time and continues due to cur = NULL
				}
				cur = cur->next;
			}
			/*all the objects other than mario, that are turtles are removed from linked list.*/


			mario->setPosition(Vector2f(512, 756));
			mario->setAsLive();
			this->isLeftPressed = false;
			this->isRightPressed = false;
			this->isUpPressed = false;
			
			timePassed = 0;

			text[0].setString("MARIO");
			text[1].setString("Press \"Space\" to Start");
			for (int i = 0; i < 2; i++)
			{
				text[i].setPosition(Vector2f((WINDOW_WIDTH - text[i].getGlobalBounds().width) / 2.0f, 200 + (i * 150)));
			}
			window->draw(text[0]);
			window->draw(text[1]);
			/*The text is set and written to the screen*/


			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
					window->close();
				else if (event.type == Event::KeyPressed)
				{
					if (Keyboard::Space == event.key.code)
						gameState = 1;
				}
			}
			/*handle close case and space key is pressed case. gameState = 1 is the game start.*/
			
		}
		else if (1 == gameState)	//handles the actual game mechanics and display it.
		{
			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
					window->close();
				else if (event.type == Event::KeyPressed)
				{
					handleKeyPres(event);
				}
				else if (event.type == Event::KeyReleased)
				{
					handleKeyRelease(event);
				}
			}
			/*handle close case and arrow keys are pressed-released cases. When an arrow key is pressed, relevant bool variable is set to 1 and when it released, it set to 0.
			The reason we implement the keyPress event like this is to achieve diagonal move when they are pressed simultaneously. More details in handleKeyPres-Release functions*/

			spawnTurtle();	//spawn a turtle as creating an object and adding it to the Object linked list at certain times.

			checkAndHandleTurtleMeet();	//Bonus #2. Check if 2 turtles have met and handle surprise and change direction.

			handleCollusion();	//handle the mario-turtle collision. One of them dies and relevant objectives are handled. The collision check is done inside of this function


			moveObjects();	//handles mario and turtle move function by traveling Object linked list.

			handleDeadTurtle();	//at every cycle, it travels the Object linked list to find a dead turtle which is fall out of the screen border. If there is, remove it.

			drawObjects();
			drawBackground(*window);
			scoreBoard->drawScoreBoard(*window);
			timePassed += 0.1;
			/*all objects, platforms and scoreBoard are drawn. Time increased 0.1 second because window refresh rate is set to 100ms.*/
		}
		else if (2 == gameState)	//handles displaying win page. 
		{
			text[0].setString("YOU WIN");
			text[1].setString("Press \"Space\" to Back Main Screen");
			for (int i = 0; i < 2; i++)
			{
				text[i].setPosition(Vector2f((WINDOW_WIDTH - text[i].getGlobalBounds().width) / 2.0f, 200 + (i * 150)));
			}
			window->draw(text[0]);
			window->draw(text[1]);
			/*The text is set and written to the screen*/

			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
					window->close();
				else if (event.type == Event::KeyPressed)
				{
					if (Keyboard::Space == event.key.code)
						gameState = 0;	//main page
				}
			}
			/*handle close case and space key is pressed case. If it is pressed, turn back to main page.*/
			
		}
		else
		{
			text[0].setString("YOU LOSE");
			text[1].setString("Press \"Space\" to Back Main Screen");
			for (int i = 0; i < 2; i++)
			{
				text[i].setPosition(Vector2f((WINDOW_WIDTH - text[i].getGlobalBounds().width) / 2.0f, 200 + (i * 150)));
			}
			window->draw(text[0]);
			window->draw(text[1]);
			/*The text is set and written to the screen*/

			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
					window->close();
				else if (event.type == Event::KeyPressed)
				{
					if (Keyboard::Space == event.key.code)
						gameState = 0;
				}
			}
			/*handle close case and space key is pressed case. If it is pressed, turn back to main page.*/
			
		}

		
		window->display();			//whatever the game state are and which objects are drawn, displays the screen.
		sleep(milliseconds(100));	//screen refresh rate is 100ms.
		
	}
}

void Game::setBackground()
{
	/*this function just sets the textures and static coordinates of the background platforms: bricks, fkoor and pipes. It is called just once at the constructor of Game*/
	this->bgTextures[0].loadFromFile("../assets/floor.png");
	this->bgTextures[1].loadFromFile("../assets/brick.png");
	this->bgTextures[2].loadFromFile("../assets/pipe.png");
	this->bgTextures[3].loadFromFile("../assets/pipeS.png");


	this->platforms = new Sprite[81];	//there are 1 floor, 4 pipes and 76 bricks = 81 sprite.
	for (int i = 0; i < 81; i++) {
		if (0 == i)
			this->platforms[i].setTexture(this->bgTextures[0]);		//platforms[0]: floor
		else if (1 == i || 2 == i)
			this->platforms[i].setTexture(this->bgTextures[2]);		//platforms[1-2]: bottom pipes
		else if (3 == i || 4 == i)
			this->platforms[i].setTexture(this->bgTextures[3]);		//platforms[3-4]: upper pipes
		else
			this->platforms[i].setTexture(this->bgTextures[1]);		//platforms[5>=]: bricks
	}


	//helper variables for setting position of backgrounds
	int brickPlatformIndexes[7] = { 0, 1, 0, 1, 0, 0, 1 };
	float brickWidth = this->platforms[5].getLocalBounds().width;
	float brickHeight = this->platforms[5].getLocalBounds().height;

	//setting position of backgrounds
	this->platforms[0].setPosition(Vector2f(0, 800));
	this->platforms[1].setScale(-1, 1);
	this->platforms[1].setPosition(0 + this->platforms[1].getLocalBounds().width, 725);
	this->platforms[2].setPosition(WINDOW_WIDTH - this->platforms[2].getLocalBounds().width, 725);
	this->platforms[3].setScale(-1, 1);
	this->platforms[3].setPosition(WINDOW_WIDTH, 50);
	this->platforms[4].setPosition(0, 50);
	for (int i = 5; i < 81; i++) {
		if (i < 17)
			this->platforms[i].setPosition(0 + (brickPlatformIndexes[0]++ * brickWidth), 600);
		else if (i < 29)
			this->platforms[i].setPosition(WINDOW_WIDTH - (brickPlatformIndexes[1]++ * brickWidth), 600);
		else if (i < 33)
			this->platforms[i].setPosition(0 + (brickPlatformIndexes[2]++ * brickWidth), 400 + (brickHeight));
		else if (i < 37)
			this->platforms[i].setPosition(WINDOW_WIDTH - (brickPlatformIndexes[3]++ * brickWidth), 400 + brickHeight);
		else if (i < 53)
			this->platforms[i].setPosition(272 + (brickPlatformIndexes[4]++ * brickWidth), 400);
		else if (i < 67)
			this->platforms[i].setPosition(0 + (brickPlatformIndexes[5]++ * brickWidth), 200);
		else
			this->platforms[i].setPosition(WINDOW_WIDTH - (brickPlatformIndexes[6]++ * brickWidth), 200);
	}
	/*all coordinates are set manually by trial and error. Since the origin is top left corner of the sprite by default, while changing scale of the pipes in sake of change
	their direction they are also shifted. Also, a brick platform attached to left border of screen use brickPlatformIndexes as 0, while brick platforms attached to right border
	of the screen use it as 1 due to the same sprite origin problem.*/
}

void Game::drawBackground(RenderWindow& window)
{
	/*This function is called at every cycle since the window is cleared at every cycle. It just travels the platform array and draw them all.*/
	for (int i = 0; i < 81; i++) {
		window.draw(this->platforms[i]);
	}	
}

Mario* Game::addMario(void)
{
	/*Create a Mario object and add it(prepend) to the Object linked list. This is called just once at the constructor of Game since we only have 1 mario.*/
	Mario* mario = new Mario(window);
	mario->next = objects;
	objects = mario;
	return mario;
}

Turtle* Game::addTurtle(void)
{
	/*Create a Turtle object and add it(prepend) to the Object linked list. Decision of which pipe it comes from is provided with the rand() function. This is called
	5 times as the game continues, at certain times.*/
	Turtle* turtle = new Turtle(window);
	turtle->next = objects;
	objects = turtle;
	if (rand() % 2)
	{
		turtle->setPosition(Vector2f(230, 80));
		objects->heading = 2;	//right
	}
	else {
		turtle->setPosition(Vector2f(795, 80));
		objects->sprite.setScale(-1, 1);
		objects->heading = 1;	//left
	}
	return turtle;
}

void Game::handleKeyPres(Event& e)
{
	/*when a key is pressed, set the relevant bool variable to 1. They will be used to send signal to mario move function*/
	if (e.key.code == Keyboard::Right)
		isRightPressed = true;
	else if (e.key.code == Keyboard::Left)
		isLeftPressed = true;
	else if (e.key.code == Keyboard::Up)
		isUpPressed = true;
}
void Game::handleKeyRelease(Event& e)
{
	/*when a key is released, set the relevant bool variable to 1. They will be used to send signal to mario move function*/
	if (e.key.code == Keyboard::Right)
		isRightPressed = false;
	else if (e.key.code == Keyboard::Left)
		isLeftPressed = false;
	else if (e.key.code == Keyboard::Up)
		isUpPressed = false;
}

void Game::handleMarioMove(void)
{
	if (mario->getIsDead())	//if mario is dead, call fall function to process mario die animation
	{
		mario->fall();
	}
	else	//if mario is not dead, this checks wheter mario is on the floor. Then, according to the key press variables, relevant signal is sent to mario move function
	{
		bool isOnFloor = onFloor(mario);
		if (isLeftPressed && isRightPressed)	//if both right and left arrow key is pressed, mario stands
		{
			mario->move(Mario::moveDirection::STAND, isOnFloor);
		}
		else if (isLeftPressed)									//if only left arrow key is pressed, mario moves to left
			mario->move(Mario::moveDirection::LEFT, isOnFloor);
		else if (isRightPressed)									//if only right arrow key is pressed, mario moves to right
			mario->move(Mario::moveDirection::RIGHT, isOnFloor);
		else	// if no key is pressed, mario stands
		{
			mario->move(Mario::moveDirection::STAND, isOnFloor);
		}
		/*the code part above handles horizontal mario move*/

		mario->jump(isOnFloor, isUpPressed);
		/*handles mario vertical move. If it is on air, it accelerates toward down. If it is on the floor, there is no vertical move unless up arrow key is pressed. When
		mario is on the floor and up arrow key is pressed, an initial vertical speed is set towards to up.*/
	}
	
}

void Game::handleTurtleMove(Object* obj)
{
	if (obj->getIsDead())	//if turtle is dead, call fall function to process turtle die animation
	{
		obj->fall();
	}
	else	//if turtle is not dead, process fall from the cliff or walk on the floor.
	{
		obj->jump(onFloor(obj));
	}
	obj->move();	//sice the dead texture is also set in this function, it is called wheter turtle is dead or alive. The correct animation will be processed inside here.
}

bool Game::onFloor(Object* obj)
{
	/*the intersectedRect variable is used to decide which side object hit the platform.*/
	FloatRect intersectedRect;
	for (int j = 0; j < 81; j++)	//the obje checks if it intersects any platform in the game at every cycle
	{
		/*for any platform, if the object intersects with it, we check how they intersect by using intersectedRect. It is defined by the "intersects" function and its value is
		the intersected rectangle of two sprite*/
		if (platforms[j].getGlobalBounds().intersects(obj->sprite.getGlobalBounds(), intersectedRect))
		{
			if (intersectedRect.width > intersectedRect.height)	//this means the object hit the platform from above or below, not sides.
			{
				if(platforms[j].getGlobalBounds().top > obj->sprite.getGlobalBounds().top)	//checks if the object is placed above the platform. So we know it hit from above.
				{
						obj->setPosition(Vector2f(obj->getPosition().x, platforms[j].getGlobalBounds().top - (obj->sprite.getGlobalBounds().height/ 2.0f) + 1)); 
						return true;
						/*if all the if checks are true, then the object is on the floor. It also set the object position exactly on the floor, but not partially inside the platform.*/
				}
			}
		}
	}
	return false;
}

bool Game::checkCollusion(Turtle* t, Mario* m, int& side)	//The mario hit the turtle from=> side 0: left, 1: below, 2: right, 3: above
{
	IntRect turtleRect = t->boundingBox();
	IntRect marioRect = m->boundingBox();
	/*get the global bounds of the mario and current turtle*/

	IntRect resRect;
	/*resRect will be the intersected rectangle of two sprite*/


	if (turtleRect.intersects(marioRect, resRect))	//if turtle and mario hit each other...
	{
		if (resRect.width > resRect.height)		//Mario hit from above or below
		{
			if (turtleRect.top > marioRect.top)		//Mario hit from above (since y index of the screen increases to the below).
				side = 3;
			else									//Mario hit from below
				side = 1;
		}
		else										//Mario hit from left or right
		{
			if (turtleRect.left < marioRect.left)	// Mario hit from right
				side = 2;
			else									//Mario hit from left
				side = 0;
		}
		return true;
	}	
	return false;
}

void Game::handleCollusion(void)
{
	/*this function travels Object linked list and checks if mario has hit any of the turtles.*/
	Object* cur = objects;
	int side;
	while (cur)
	{
		if (dynamic_cast<Mario*>(cur) == NULL)
		{
			if (checkCollusion(static_cast<Turtle*>(cur), mario, side))
			{
				/*if Mario hit from left or right and turtle is able to kill (not dead or halfDead), mario should die. If turtle is half dead and mario is able to kill (is alive), then it dies*/
				if ((0 == side || 2 == side))				//it gives a time interval to turtle to be able to die after it set as half dead
				{													//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
					if (static_cast<Turtle*>(cur)->getIsHalfDead() && static_cast<Turtle*>(cur)->getCanDie() && mario->canKill)
						handleTurtleDie(cur);
					else if (cur->canKill)
						handleMarioDie();
				}
				else if ((3 == side) && mario->canKill)	//if Mario hit from above and the mario is able to kill (is alive), turtle should die
				{
					handleTurtleDie(cur);
					mario->setVerticalSpeed(-12);		// if Mario hit from above, it also bounce of the turtle shell.
				}
				else if (1 == side && mario->canKill)	//if Mario hit from below and the mario is able to kill (is alive), turtle should half die
				{
					static_cast<Turtle*>(cur)->setVerticalSpeed(-12);	// if Mario hit from below, the turtle also bounce.
					static_cast<Turtle*>(cur)->setIsHalfDead(true);
					cur->state = 4;
				}
			}
		}
		cur = cur->next;
	}
}

void Game::drawObjects(void)
{
	/*travel the Object linked list and draw all of their sprites.*/
	Object* cur = objects;
	while (cur)
	{
		cur->draw(*window);
		cur = cur->next;
	}
}

void Game::spawnTurtle(void)
{
	/*Spawns 5 turtles at the certain times. In this case, it spawn 1, 7, 14, 17 and 25 seconds after the game start.*/
	if (1.05 < timePassed && timePassed < 1.15)
		addTurtle();
	else if (7.05 < timePassed && timePassed < 7.15)
		addTurtle();
	else if (14.05 < timePassed && timePassed < 14.15)
		addTurtle();
	else if (17.05 < timePassed && timePassed < 17.15)
		addTurtle();
	else if (25.05 < timePassed && timePassed < 25.15)
		addTurtle();
}

void Game::moveObjects(void)
{
	/*travels the Object linked list and calls relevant handle move function of the objects. This can be implemented using polymorphism, however especially handlemariomove 
	function is using lots of variables from the game class and sending all of them as parameters is not make sence we think.*/
	Object* cur = objects;
	while (cur)
	{
		if (dynamic_cast<Mario*>(cur) != NULL)
			handleMarioMove();
		else
			handleTurtleMove(cur);
		cur = cur->next;
	}
}

void Game::handleMarioDie(void)
{
	/*This function is called when mario hit a turtle from sides. Because of this, this function will be called lots of time when mario dies and before go outside of the 
	turtle rectangle area. So it should check if the mario is already dead before it decreases the live count. But when it does decrease it, it also checks if the player
	has any live and if they has not, the game finishes as lose.*/
	if (!mario->getIsDead())
	{
		scoreBoard->setLives(scoreBoard->getLives() - 1);
		if (scoreBoard->getLives() == 0)
			gameState = 3;
	}
	mario->setAsDead();
}

void Game::handleTurtleDie(Object* obj)
{
	/*This function is called when mario hit the turtle from above(or any side when turtle is half dead). Because of this, this function will be called lots of time when turtle 
	die and before it go outside of the mario rectangle area. So it should check if the turtle is already dead before it increases the player point. But when it does increas, it 
	alsco checks if the player has reached 500 point and if they has, the game finishes as win.*/
	if (!obj->getIsDead())
	{
		int score = stoi(scoreBoard->getScore());
		score += 100;
		if (500 == score)
			gameState = 2;
		scoreBoard->setScore(score);
	}
	obj->setAsDead();
}

void Game::removeObject(Object* obj)
{
	/*removes the object from the Object linked list by travelling. The "prev" variable is used to properly remove an object at the middle of the list. The previous object of
	the removed object should point the next object of the removed one.*/
	Object* cur = objects;
	Object* prev = NULL;
	while (cur) {
		if (cur == obj) {
			if (prev) {
				prev->next = cur->next;
			}
			else {
				objects = cur->next;
			}
			delete cur;
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}

void Game::handleDeadTurtle(void)
{
	/*Travels the Object linked list and if it find a dead turtle which is fall below the bottom border of the screen, it removes it. Since it removes only the first turtle
	that satisfy the conditions, this function is called every cycle.*/
	Object* cur = objects;
	while (cur)
	{
		if (dynamic_cast<Turtle*>(cur) != NULL)
		{
			if (cur->getIsDead() && cur->boundingBox().top >= WINDOW_HEIGHT + 100)
			{
				removeObject(cur);
				return;
			}
		}
		cur = cur->next;
	}
}

void Game::checkAndHandleTurtleMeet(void)
{
	/*with a double loop on Object linked list...*/
	Object* cur = objects;
	Object* other = objects->next;
	FloatRect curRect, otherRect;
	while (cur)
	{
		while (other)
		{
			/*if both cur and other points to a turtle object and they are not the same objects (also they both are alive)...*/
			if (dynamic_cast<Turtle*>(cur) != NULL && dynamic_cast<Turtle*>(other) != NULL && cur != other && !(static_cast<Turtle*>(cur)->getIsHalfDead()) && !(static_cast<Turtle*>(other)->getIsHalfDead()) && !cur->getIsDead() && !other->getIsDead())
			{
				curRect = cur->sprite.getGlobalBounds();
				otherRect = other->sprite.getGlobalBounds();
				/*checks if a turtle has collision with an other turtle.*/
				if (curRect.intersects(otherRect))
				{
					/*if the left one is heading right and the right one is heading left, they goes into surprise state and change headings.*/
					if (curRect.left < otherRect.left && cur->heading == 2 && other->heading == 1)
					{
						cur->heading = 1;
						other->heading = 2;						
						cur->state = 3;
						other->state = 3;
					}
					else if (curRect.left > otherRect.left && cur->heading == 1 && other->heading == 2)	//vice versa
					{
						cur->heading = 2;
						other->heading = 1;
						cur->state = 3;
						other->state = 3;
					}
				}
			}
			other = other->next;
		}
		cur = cur->next;
		if(cur)
			other = cur->next;
	}
}
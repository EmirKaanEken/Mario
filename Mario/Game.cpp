#include "Game.h"

Game::Game() {
	this->isLeftPressed = false;
	this->isRightPressed = false;
	this->isUpPressed = false;
	this->timePassed = 0;
	window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");

	this->setBackground();

	mario = addMario();
	mario->setPosition(Vector2f(512, 756));

	scoreBoard = new ScoreBoard(mario->getLiveTexture());

	font.loadFromFile("../assets/font.ttf");
	for (int i = 0; i < 2; i++)
	{
		text[i].setFont(font);
		text[i].setFillColor(Color::Magenta);
	}
	
	text[0].setCharacterSize(120);
	//text[0].setPosition(Vector2f(300, 200));
	//text[1].setPosition(Vector2f(300, 400));

	gameState = 0;
}

void Game::update(void) {
	while (window->isOpen())
	{
		Event event;

		window->clear();

		if (0 == gameState)
		{
			scoreBoard->setLives(3);
			scoreBoard->setScore(0);

			//Burada tüm objeler silinecek ve mario ortaya yeniden konumlandýrýlacak
			Object* cur = objects;
			while (cur)
			{
				if (dynamic_cast<Mario*>(cur) == NULL)
				{
					removeObject(cur);
					cur = objects;		//özellikle burda bunu yapmaktan memnun deðilim ama, cur silinince next'ini alamadýðýmýz için baþtan objects'e eþitliyorum, sadece mario kalmýþsa bi döngü gönüp null oluyo zaten
				}
				cur = cur->next;
			}
			mario->setPosition(Vector2f(512, 756));
			mario->setAsLive();
			
			timePassed = 0;

			text[0].setString("MARIO");
			text[1].setString("Press \"Space\" to Start");
			for (int i = 0; i < 2; i++)
			{
				text[i].setPosition(Vector2f((WINDOW_WIDTH - text[i].getGlobalBounds().width) / 2.0f, 200 + (i * 150)));
			}

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
			window->draw(text[0]);
			window->draw(text[1]);
		}
		else if (1 == gameState)
		{
			while (window->pollEvent(event))
			{
				Vector2f prePos = mario->getPosition();
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

			spawnTurtle();

			handleCollusion();


			moveObjects();

			handleDeadTurtle();


			//window->clear();

			drawObjects();
			drawBackground(*window);
			scoreBoard->drawScoreBoard(*window);
			timePassed += 0.1;
		}
		else if (2 == gameState)
		{
			text[0].setString("YOU WIN");
			text[1].setString("Press \"Space\" to Back Main Screen");
			for (int i = 0; i < 2; i++)
			{
				text[i].setPosition(Vector2f((WINDOW_WIDTH - text[i].getGlobalBounds().width) / 2.0f, 200 + (i * 150)));
			}

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
			window->draw(text[0]);
			window->draw(text[1]);
		}
		else
		{
			text[0].setString("YOU LOSE");
			text[1].setString("Press \"Space\" to Back Main Screen");
			for (int i = 0; i < 2; i++)
			{
				text[i].setPosition(Vector2f((WINDOW_WIDTH - text[i].getGlobalBounds().width) / 2.0f, 200 + (i * 150)));
			}

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
			window->draw(text[0]);
			window->draw(text[1]);
		}

		
		window->display();
		sleep(milliseconds(100));
		
	}
}

void Game::setBackground()
{
	this->bgTextures[0].loadFromFile("../assets/floor.png");
	this->bgTextures[1].loadFromFile("../assets/brick.png");
	this->bgTextures[2].loadFromFile("../assets/pipe.png");
	this->bgTextures[3].loadFromFile("../assets/pipeS.png");

	//setting textures of backgrounds
	this->platforms = new Sprite[81];
	for (int i = 0; i < 81; i++) {
		if (0 == i)
			this->platforms[i].setTexture(this->bgTextures[0]);
		else if (1 == i || 2 == i)
			this->platforms[i].setTexture(this->bgTextures[2]);
		else if (3 == i || 4 == i)
			this->platforms[i].setTexture(this->bgTextures[3]);
		else
			this->platforms[i].setTexture(this->bgTextures[1]);
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
}

void Game::drawBackground(RenderWindow& window)
{
	for (int i = 0; i < 81; i++) {
		window.draw(this->platforms[i]);
	}	
}

Mario* Game::addMario(void)
{
	Mario* mario = new Mario(window);
	mario->next = objects;
	objects = mario;
	return mario;
}

Turtle* Game::addTurtle(void)
{
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
	if (e.key.code == Keyboard::Right)
		isRightPressed = true;
	else if (e.key.code == Keyboard::Left)
		isLeftPressed = true;
	else if (e.key.code == Keyboard::Up)
		isUpPressed = true;
}
void Game::handleKeyRelease(Event& e)
{
	if (e.key.code == Keyboard::Right)
		isRightPressed = false;
	else if (e.key.code == Keyboard::Left)
		isLeftPressed = false;
	else if (e.key.code == Keyboard::Up)
		isUpPressed = false;
}

void Game::handleMarioMove(void)
{
	if (mario->getIsDead())	//bu if'in içinde fall fonksiyonu çaðýrýlabilir ve burdaki iþ oraya verilebilir.
	{
		mario->move(Mario::moveDirection::DEAD, false);
		mario->jump(false, false);
		if (mario->boundingBox().top > WINDOW_HEIGHT + 50)
		{
			mario->setAsLive();
			mario->setPosition(Vector2f(512, 600));
		}
	}
	else
	{
		bool isOnFloor = onFloor(mario);
		if (isLeftPressed && isRightPressed)
		{
			mario->move(Mario::moveDirection::STAND, isOnFloor);
		}
		/*else if (isLeftPressed && isUpPressed)
			mario->setPosition(Vector2f(100, 100));	//will handle upper left
		else if (isRightPressed && isUpPressed)
			mario->setPosition(Vector2f(500, 500));	//will handle upper right*/
		else if (isLeftPressed)
			mario->move(Mario::moveDirection::LEFT, isOnFloor);
		else if (isRightPressed)
			mario->move(Mario::moveDirection::RIGHT, isOnFloor);
		else if (isUpPressed)
			mario->move(Mario::moveDirection::UP, isOnFloor);
		else	// no key is pressed
		{
			mario->move(Mario::moveDirection::STAND, isOnFloor);
		}

		mario->jump(isOnFloor, isUpPressed);
	}
	
}

void Game::handleTurtleMove(Object* obj)
{
	bool deadFlag = false;
	if (obj->getIsDead())
	{
		obj->state = 4;
		obj->jump(false);
		/*if (obj->boundingBox().top >= WINDOW_HEIGHT + 50)
		{
			removeObject(obj);
			deadFlag = true;
		}*/
	}
	else
	{
		obj->jump(onFloor(obj));
	}
	//if(!deadFlag)
	obj->move();
}

bool Game::onFloor(Object* obj)
{
	/*Burada þu an width falan karþýlaþtýrarak, aslýnda platformla çakýþtýðý taraflarý ayýrmaya baþladým. Genel bi checkHit fonksiyonuna bunlarýn çoðunu
	geçirip, burada sadece ilgili fonksiyonu çaðýrýp onun geri dönüþüne göre true false dönerim mesela, o fonksiyonun diðer çýktýlarý için de baþka 
	fonksiyonlarda iþ yaparým*/
	FloatRect intersectedRect;
	for (int j = 0; j < 81; j++)
	{
		if (platforms[j].getGlobalBounds().intersects(obj->sprite.getGlobalBounds(), intersectedRect))
		{
			if (intersectedRect.width > intersectedRect.height)
			{
				if(platforms[j].getGlobalBounds().top > obj->sprite.getGlobalBounds().top)
				{
						obj->setPosition(Vector2f(obj->getPosition().x, platforms[j].getGlobalBounds().top - (obj->sprite.getGlobalBounds().height/ 2.0f) + 1)); //biraz içeri girseler de en tepeye çýksýn diye koydum ama iþlem hýzýný yavaþlattýðý için bazen platform içinden geçilmesine sebep luyo
						return true;
				}
			}
		}
	}
	return false;
}

bool Game::checkCollusion(Turtle* t, Mario* m, int& side)	//Mario, side 0: soldan, 1: aþaðýdan, 2: saðdan, 3: üstten çarptý turtle'a
{
	IntRect turtleRect = t->boundingBox();
	IntRect marioRect = m->boundingBox();
	IntRect resRect;
	if (turtleRect.intersects(marioRect, resRect))
	{
		if (resRect.width > resRect.height)
		{
			if (turtleRect.top > marioRect.top)
				side = 3;
			else
				side = 1;
		}
		else
		{
			if (turtleRect.left < marioRect.left)
				side = 2;
			else
				side = 0;
		}
		return true;
	}	
	return false;
}

void Game::handleCollusion(void)
{
	Object* cur = objects;
	int side;
	while (cur)
	{
		if (dynamic_cast<Mario*>(cur) == NULL)
		{
			if (checkCollusion(static_cast<Turtle*>(cur), mario, side))
			{
				//cout << "Çarpýþtý, side: " << side << endl;
				if ((0 == side || 2 == side) && cur->canKill)
				{
					handleMarioDie();
				}
				else if((1 == side || 3 == side) && mario->canKill)
				{
					handleTurtleDie(cur);
					if(3 == side)
						mario->setVerticalSpeed(-12);
				}
			}
		}
		cur = cur->next;
	}
}

void Game::drawObjects(void)
{
	Object* cur = objects;
	while (cur)
	{
		cur->draw(*window);
		cur = cur->next;
	}
}

void Game::spawnTurtle(void)
{
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
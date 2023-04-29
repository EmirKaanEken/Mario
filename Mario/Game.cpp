#include "Game.h"

Game::Game() {
	this->isLeftPressed = false;
	this->isRightPressed = false;
	this->isUpPressed = false;
	window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");

	this->setBackground(*window);

	mario = new Mario(window);
	mario->setPosition(Vector2f(512, 756));


}

void Game::update(void) {
	while (window->isOpen())
	{
		Event event;

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


		handleMarioMove();

		window->clear();

		mario->draw(*window);

		drawBackground(*window);
		window->display();

		sleep(milliseconds(100));
	}
}

void Game::setBackground(RenderWindow& window)
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

Turtle* Game::addTurtle(void)
{
	Turtle* turtle = new Turtle(window);
	turtle->next = objects;
	objects = turtle;
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
	if (isLeftPressed && isRightPressed)
	{
		//Do nothing, Perhaps we allow it to jump if it is pressed three key simultaneously
	}
	/*else if (isLeftPressed && isUpPressed)
		mario->setPosition(Vector2f(100, 100));	//will handle upper left
	else if (isRightPressed && isUpPressed)
		mario->setPosition(Vector2f(500, 500));	//will handle upper right*/
	else if (isLeftPressed)
		mario->move(Mario::moveDirection::LEFT);
	else if(isRightPressed)
		mario->move(Mario::moveDirection::RIGHT);
	else if(isUpPressed)
		mario->move(Mario::moveDirection::UP);

	mario->jump(onFloor(mario), isUpPressed);
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
				for (int i = 0; i < obj->sprite.getGlobalBounds().width; i++) {
					if (platforms[j].getGlobalBounds().contains(Vector2f(obj->sprite.getGlobalBounds().left + i, obj->sprite.getGlobalBounds().top + obj->sprite.getGlobalBounds().height)))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
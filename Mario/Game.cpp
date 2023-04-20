#include "Game.h"

Game::Game() {
	window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");

	this->groundTexture.loadFromFile("../assets/floor.png");
	this->brickTexture.loadFromFile("../assets/brick.png");
	this->lowerPipeTexture.loadFromFile("../assets/pipe.png");
	this->upperPipeTexture.loadFromFile("../assets/pipeS.png");

	/*this->ground.setTexture(this->groundTexture);
	this->lowerPipes[0].setTexture(this->lowerPipeTexture);
	this->lowerPipes[1].setTexture(this->lowerPipeTexture);
	//burada flip yapýlacak lowerpipes[0] için
	this->upperPipes[0].setTexture(this->upperPipeTexture);
	this->upperPipes[1].setTexture(this->upperPipeTexture);
	//burada flip yapýlacak upperpipes[0] için

	for (int i = 0; i < 76; i++) {
		this->bricks[i].setTexture(brickTexture);
	}*/
	

	//setting textures of backgrounds
	this->platforms = new Sprite[81];
	for (int i = 0; i < 81; i++) {
		if (0 == i)
			this->platforms[i].setTexture(this->groundTexture);
		else if (1 == i || 2 == i)
			this->platforms[i].setTexture(this->lowerPipeTexture);
		else if (3 == i || 4 == i)
			this->platforms[i].setTexture(this->upperPipeTexture);
		else
			this->platforms[i].setTexture(this->brickTexture);
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

	mario = new Mario(window);
	mario->setPosition(Vector2f(479, 712));


}

void Game::update(void) {
	while (window->isOpen())
	{
		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}

		window->clear();

		mario->draw(*window);

		drawBackground(*window);
		window->display();

		sleep(milliseconds(100));
	}
}

void Game::drawBackground(RenderWindow& window)
{
	//this->ground.setPosition(Vector2f(0, 800));
	//window.draw(this->ground);
	

	/*this->lowerPipes[0].setPosition(0 + lowerPipes[0].getLocalBounds().width, 725);
	this->lowerPipes[0].setScale(-1,1);
	window.draw(this->lowerPipes[0]);*/
	

	/*this->lowerPipes[1].setPosition(WINDOW_WIDTH - lowerPipes[1].getLocalBounds().width, 725);
	window.draw(this->lowerPipes[1]);*/
	

	/*this->upperPipes[0].setPosition(WINDOW_WIDTH, 50);
	this->upperPipes[0].setScale(-1, 1);
	window.draw(this->upperPipes[0]);*/
	

	/*this->upperPipes[1].setPosition(0, 50);
	window.draw(this->upperPipes[1]);*/
	


	/*for (int i = 0; i < 12; i++) {

		this->bricks[i].setPosition(0 + (i * this->bricks[0].getLocalBounds().width), 600);
		window.draw(this->bricks[i]);
	}

	for (int i = 0; i < 12; i++) {
		this->bricks[12 + i].setPosition(WINDOW_WIDTH - ((i+1) * this->bricks[0].getLocalBounds().width), 600);
		window.draw(this->bricks[12 + i]);
	}

	for(int i = 0; i < 4; i++){
		this->bricks[24 + i].setPosition(0 + (i * this->bricks[0].getLocalBounds().width), 400 + (this->bricks[0].getLocalBounds().height));
		window.draw(this->bricks[24 + i]);
	}
	
	for (int i = 0; i < 4; i++) {
		this->bricks[28 + i].setPosition(WINDOW_WIDTH - ((i+1) * this->bricks[0].getLocalBounds().width), 400 + (this->bricks[0].getLocalBounds().height));
		window.draw(this->bricks[28 + i]);
	}
	
	for (int i = 0; i < 16; i++) {
		this->bricks[32 + i].setPosition(272 + (i * this->bricks[0].getLocalBounds().width), 400);
		window.draw(this->bricks[32 + i]);
	}

	for (int i = 0; i < 14; i++) {
		this->bricks[48 + i].setPosition(0 + (i * this->bricks[0].getLocalBounds().width), 200);
		window.draw(this->bricks[48 + i]);
	}

	for (int i = 0; i < 14; i++) {
		this->bricks[62 + i].setPosition(WINDOW_WIDTH - ((i + 1) * this->bricks[0].getLocalBounds().width), 200);
		window.draw(this->bricks[62 + i]);
	}*/
	
	

	/*yoruma alýnan kýsým yerine bu kullanýlýyor çünkü mario'nun platformlarla olan collision'ýný hesaplamak tek bir array üstünden daha kolay olacak.*/

	for (int i = 0; i < 81; i++) {
		window.draw(this->platforms[i]);
	}

	
}
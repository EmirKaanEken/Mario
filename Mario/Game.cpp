#include "Game.h"

Game::Game() {
	window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");

	this->groundTexture.loadFromFile("../assets/floor.png");
	this->brickTexture.loadFromFile("../assets/brick.png");
	this->lowerPipeTexture.loadFromFile("../assets/pipe.png");
	this->upperPipeTexture.loadFromFile("../assets/pipeS.png");

	this->ground.setTexture(this->groundTexture);
	this->lowerPipes[0].setTexture(this->lowerPipeTexture);
	this->lowerPipes[1].setTexture(this->lowerPipeTexture);
	//burada flip yapýlacak lowerpipes[0] için
	this->upperPipes[0].setTexture(this->upperPipeTexture);
	this->upperPipes[1].setTexture(this->upperPipeTexture);
	//burada flip yapýlacak upperpipes[0] için

	for (int i = 0; i < 76; i++) {
		this->bricks[i].setTexture(brickTexture);
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
	this->ground.setPosition(Vector2f(0, 800));
	window.draw(this->ground);

	this->lowerPipes[0].setPosition(0 + lowerPipes[0].getLocalBounds().width, 725);
	this->lowerPipes[0].setScale(-1,1);
	window.draw(this->lowerPipes[0]);

	this->lowerPipes[1].setPosition(WINDOW_WIDTH - lowerPipes[1].getLocalBounds().width, 725);
	window.draw(this->lowerPipes[1]);

	for (int i = 0; i < 12; i++) {

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
	}

	this->upperPipes[0].setPosition(WINDOW_WIDTH, 50);
	this->upperPipes[0].setScale(-1,1);
	window.draw(this->upperPipes[0]);

	this->upperPipes[1].setPosition(0, 50);
	window.draw(this->upperPipes[1]);
}
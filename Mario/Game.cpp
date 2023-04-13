#include "Game.h"

Game::Game() {
	window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");

	mario = new Mario(window);
	mario->setPosition(Vector2f(40, 40));


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

		window->display();

		sleep(milliseconds(100));
	}
}
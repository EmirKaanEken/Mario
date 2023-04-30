#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(Texture t)
{
	score = "000000";
	lives = 3;
	font.loadFromFile("../assets/font.ttf");
	text.setFont(font);
	//text.setColor(Color::White);
	text.setStyle(Text::Bold);
	text.setPosition(Vector2f(170, 10));
	headTexture = t;
}

void ScoreBoard::drawScoreBoard(RenderWindow& window)
{
	text.setString(score);

	int liveStartAddr = 250;
	for (int i = 0; i < lives; i++)
	{
		Sprite head;
		head.setTexture(headTexture);
		head.setPosition(Vector2f(250 + (i*50), 50));
		window.draw(head);
	}

	window.draw(text);
}
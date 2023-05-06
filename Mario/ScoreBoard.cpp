#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(Texture t)
{
	score = "000000";
	lives = 3;
	font.loadFromFile("../assets/font.ttf");
	text.setFont(font);
	text.setStyle(Text::Bold);
	text.setPosition(Vector2f(170, 10));
	headTexture = t;		//since the mario head texture is stored in the Mario class and scoreboard should access it to display it, it takes it as a variable
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
	/*it draws as many mamrio heads as the according to the "live" variable with 50 px gaps.*/


	/*"text" variable contains current score.*/
	window.draw(text);
}
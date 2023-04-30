#pragma once
#include "Common.h"

class ScoreBoard {
	string score;
	int lives;
	Font font;
	Text text;
	Texture headTexture;
public:
	ScoreBoard(Texture);
	void setScore(int score) { this->score = "000" + to_string(score); }
	void setLives(int lives) { this->lives = lives; }
	int getLives(void) { return this->lives; }
	string getScore(void) { return this->score; }
	void drawScoreBoard(RenderWindow&);
};
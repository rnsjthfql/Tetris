#pragma once
#include <string.h>

class Player
{
private:
	char name[10];
	int score;
public:
	Player() : score(0)
	{ }
	int GetScore();
	void SetScore(int num);
	void SetName(char n[10]);
	char* GetName();
};


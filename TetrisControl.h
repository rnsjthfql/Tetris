#pragma once
#include "Player.h"
#include <iostream>
#include <iomanip>
using namespace std;

#define ROW 25
#define COL 15

class TetrisControl {
private:
	Player* plr[5];
	int** map;
	int pnum;
	int score;
	int c = 0;
public:
	TetrisControl();
	void SetPlayer(Player* p);
	void InitMap();
	void UpdateMap();
	void DeleteLine();
	void ShowMap();
	void ShowLose();
	int GetC();
	int GetScore();
	~TetrisControl();

	int*& operator[](const int& idx) {
		return map[idx];
	}
};
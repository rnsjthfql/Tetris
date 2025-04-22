#include "TetrisControl.h"

TetrisControl::TetrisControl()
{
	k = 0;
	score = 0;
	pnum = 0;
	map = new int*[ROW];
	for (int i = 0; i < ROW; i++) {
			map[i] = new int[COL];
	}
}

void TetrisControl::SetPlayer(Player* p)
{
	for (int i = 0; i < pnum; i++) {
		if (pnum == 0) {
			plr[0] = p;
			break;
		}
		if (p->GetScore() >= plr[i]->GetScore()) {
			for (i; i < pnum - 1; i++) {
				plr[++i] = plr[i];
			}
			plr[i] = p;
			break;
		}
	}
}

void TetrisControl::InitMap()
{

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i == 0 || i == ROW - 1)
				map[i][j] = 4;
			else if (j == 0 || j == COL - 1)
				map[i][j] = 4;
			else
				map[i][j] = 0;
		}
	}
}

void TetrisControl::UpdateMap()
{
	for (int i = 1; i < ROW - 1; i++) {
		for (int j = 1; j < COL - 1; j++) {
			if (map[i][j] == 1)
				map[i][j] = 1;
			else if (map[i][j] == 2)
				map[i][j] = 2;
			else if (map[i][j] == 4)
				map[i][j] = 4;
			else
				map[i][j] = 0;
		}
	}
}

bool TetrisControl::DeleteLine()
{
	int n = 0;
	for (int i = ROW-2; i >= 1; i--) {
		n = 0;
		for (int j = COL-2; j >= 1 ; j--) {
			if (map[i][j] == 2)
				n += 1;
			if (n == COL-2) {
				k = i;
				return true;
			}
		}
	}
	return false;
}

void TetrisControl::ShowMap()
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (map[i][j] == 4)
				cout << "#" << setw(2);
			else if (map[i][j] == 1)
				cout << "□" << setw(2);
			else if (map[i][j] == 2)
				cout << "■" << setw(2);
			else
				cout << " " << setw(2);
		}
		cout << endl;
	}
}

void TetrisControl::ShowLose()
{
	for (int j = 1; j < COL - 1; j++) {
		if (map[1][j] == 2) {
			c = 1; //졌음을 표시
			cout << "YOU LOSE!!!" << endl;
			break;
		}
	}
}

int TetrisControl::GetK()
{
	return k;
}

int TetrisControl::GetC()
{
	return c;
}

int TetrisControl::GetScore()
{
	return score;
}

TetrisControl::~TetrisControl()
{
	for (int i = 0; i < ROW; i++) {
		delete[] map[i];
	}
	delete[] map;
}

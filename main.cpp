#include "Block.h"
#include "TetrisControl.h"
#include "Player.h"
#include <iostream>
#include <conio.h>
#include <random>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define ROW 25
#define COL 15


void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void cursor(int n) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = n;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int block[3][3] = { 0 };

int main() {
	TetrisControl tc;
	srand((unsigned int)time(NULL));
	time_t start, t;

	int rot = rand() % 4;		//랜덤회전
	int randNum = rand() % 5;	//랜덤블록
	int score = 0;


	tc.InitMap();
	//tc.ShowMap();
	
	for (int j = 1; j < COL - 1; j++) {
		if (j == 7) {
			tc[ROW-2][j] = 0;
		}
		else
			tc[ROW - 2][j] = 2;
	}
	

	int key = 0, x = 7, y = 1;
	Block b = Block();
	int k = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			block[i][j] = b[rot][randNum][k];
			k++;
		}
	}

	key = _getch();

	while (1) {
		gotoxy(0, 0);
		cursor(0);
		
		tc.ShowMap();
		tc.UpdateMap();
		tc.ShowLose();
		if (tc.GetC() == 1) {
			cout << "프로그램을 종료합니다." << endl;
			return 0;
		}


		if (tc.DeleteLine() == true) {
			for (int i = tc.GetK(); i >= 1; i--) {
				for (int j = 1; j < COL - 1; j++) {
					tc[i][j] = tc[i - 1][j];
					tc[1][j] = 0;
				}
			}
			score += 10;
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (tc[i + y][j + x] == 2) {
					tc[i + y][j + x] = 2;
				}
				else
					tc[i + y][j + x] = 0;
			}
		}



		y += 1;
		int nowy = y;
		int nowx = x;


		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (block[i][j] == 1) {
					tc[i + y][j + x] = 1;
				}
			}
		}

		for (int i = 2; i >= 0; i--) {
			for (int j = 2; j >= 0; j--) {
				if (tc[i + y][j + x] == 2) {
					tc[i + y][j + x] = 2;
				}
				if (block[i][j] == 0 && tc[i + y][j + x] == 2) {
					tc[i + y][j + x] = 2;
				}
				if (tc[i + y][j + x] == 1 && block[i][j] == 2) {
					tc[i + y][j + x] = 2;
				}
				if (block[i][j] == 2) {
					tc[i + y][j + x] = 2;
				}
				if (y == ROW - 4 && block[i][j] == 1) {
					block[i][j] = 2;
					tc[i + y][j + x] = 2;
				}
				if (i+y+1 < ROW-1 && block[i][j] == 1 && tc[i + y + 1][j + x] == 2) {
					if (j >= 1 && block[i][j - 1] == 1 && tc[i + y + 1][j + x - 1] != 2) {
						if (j == 2 && block[i][j - 2] == 1 && tc[i + y + 1][j + x - 1] != 2) {
							block[i][j - 2] = 2;
							tc[i + y][j + x - 2] = 2;
						}
						else {
							block[i][j - 1] = 2;
							tc[i + y][j + x - 1] = 2;
						}
					}
					else {
						block[i][j] = 2;
						tc[i + y][j + x] = 2;
					}
				}

				for (int i = 2; i >= 0; i--) {		//사방에 2가 있는지 확인
					for (int j = 2; j >= 0; j--) {
						if (j - 1 >= 0 && block[i][j - 1] == 2 && block[i][j] == 1) {
							block[i][j] = 2;
							tc[i + y][j + x] = 2;
						}
						if (i - 1 >= 0 && block[i - 1][j] == 2 && block[i][j] == 1) {
							block[i][j] = 2;
							tc[i + y][j + x] = 2;
						}
						if (i + 1 < 3 && block[i + 1][j] == 2 && block[i][j] == 1) {
							block[i][j] = 2;
							tc[i + y][j + x] = 2;
						}
						if (j + 1 < 3 && block[i][j + 1] == 2 && block[i][j] == 1) {
							block[i][j] = 2;
							tc[i + y][j + x] = 2;
						}
						if (tc[i + y][j + x] == 1 && block[i][j] == 2) {
							tc[i + y][j + x] = 2;
						}

					}

				}
				if (block[i][j] == 2) {
					tc[i + y][j + x] = 2;
				}

			}
		}

		for (int i = 2; i >= 0; i--) {
			for (int j = 2; j >= 0; j--) {
				if (block[i][j] == 0 && tc[i + y][j + x] == 2) {
					tc[i + y][j + x] = 2;
				}
				if (y == ROW - 4 && block[i][j] == 1) {
					block[i][j] = 2;
					tc[i + y][j + x] = 2;
				}
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (block[i][j] == 2)
					y = ROW - 4;
			}
		}


		if (y > ROW - 4)
			y = ROW - 4;


		//블록 생성
		if (y == ROW - 4) {
			rot = rand() % 4;
			randNum = rand() % 5;

			x = 7, y = 1;
			Block b = Block();
			k = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					block[i][j] = b[rot][randNum][k];
					k++;
					if(block[i][j] == 1)
						tc[i + y][j + x] = 1;
				}
			}

			for (int i = 2; i >= 0; i--) {
				for (int j = 2; j >= 0; j--) {
					if (tc[i + y][j + x] == 2) {
						tc[i + y][j + x] = 2;
					}
					if (tc[i + y][j + x] == 1 && block[i][j] == 2) {
						tc[i + y][j + x] = 2;
					}
					if (block[i][j] == 2) {
						tc[i + y][j + x] = 2;
					}
					if (y == ROW - 4 && block[i][j] == 1) {
						block[i][j] = 2;
						tc[i + y][j + x] = 2;
					}
					if (block[i][j] == 1 && tc[i + y + 1][j + x] == 2) {
						if (j >= 1 && block[i][j - 1] == 1 && tc[i + y + 1][j + x - 1] != 2) {
							if (j == 2 && block[i][j - 2] == 1 && tc[i + y + 1][j + x - 1] != 2) {
								block[i][j] = 2;
								block[i][j - 2] = 2;
								tc[i + y][j + x - 2] = 2;
							}
							else {
								block[i][j] = 2;
								block[i][j - 1] = 2;
								tc[i + y][j + x - 1] = 2;
							}
						}
						else {
							block[i][j] = 2;
							tc[i + y][j + x] = 2;
						}
					}

					for (int i = 2; i >= 0; i--) {		//사방에 2가 있는지 확인
						for (int j = 2; j >= 0; j--) {
							if (j - 1 >= 0 && block[i][j - 1] == 2 && block[i][j] == 1) {
								block[i][j] = 2;
								tc[i + y][j + x] = 2;
							}
							if (i - 1 >= 0 && block[i - 1][j] == 2 && block[i][j] == 1) {
								block[i][j] = 2;
								tc[i + y][j + x] = 2;
							}
							if (i + 1 < 3 && block[i + 1][j] == 2 && block[i][j] == 1) {
								block[i][j] = 2;
								tc[i + y][j + x] = 2;
							}
							if (j + 1 < 3 && block[i][j + 1] == 2 && block[i][j] == 1) {
								block[i][j] = 2;
								tc[i + y][j + x] = 2;
							}
							if (tc[i + y][j + x] == 1 && block[i][j] == 2) {
								tc[i + y][j + x] = 2;
							}

						}

					}
					if (block[i][j] == 2) {
						tc[i + y][j + x] = 2;
					}
					
				}
			}
		}

		gotoxy(35, 10);
		cout << "↑: 블록 회전" << endl;
		gotoxy(35, 11);
		cout << "↓: 블록 아래로 이동" << endl;
		gotoxy(35, 12);
		cout << "→: 블록 오른쪽으로 이동" << endl;
		gotoxy(35, 13);
		cout << "←: 블록 왼쪽으로 이동" << endl;
		gotoxy(35, 14);
		cout << "ESC: 게임 종료" << endl;

		Sleep(300);

		if (_kbhit()) {

			key = _getch();

			if (key == UP) {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						tc[i + y][j + x] = 0;
					}
				}

				gotoxy(x, y);
				++rot;
				rot = rot % 4;
				k = 0;
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						block[i][j] = b[rot][randNum][k];
						k++;
						tc[i + y][j + x] = block[i][j];
					}
				}
				tc.UpdateMap();

			}
			else if (key == DOWN) {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if(tc[i + y][j + x] == 1)
							tc[i + y][j + x] = 0;
					}
				}
				
				++y;
				if (y > ROW - 4)
					y = ROW - 4;

				gotoxy(x, y);
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if (block[i][j] == 1)
							tc[i + y][j + x] = 1;
						if (tc[i + y][j + x] == 2)
							tc[i + y][j + x] = 2;
					}
				}
				tc.UpdateMap();
			}
			else if (key == LEFT) {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if (tc[i + y][j + x] == 1)
							tc[i + y][j + x] = 0;
					}
				}

				
				--x;
				if (x < 1)
					x = 1;
				
				gotoxy(x, y);
				
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if(block[i][j]==1)
							tc[i + y][j + x] = 1;
						if (tc[i + y][j + x] == 2)
							tc[i + y][j + x] = 2;
					}
				}
				tc.UpdateMap();
			}
			else if (key == RIGHT) {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if(tc[i+y][j+x] == 1)
							tc[i + y][j + x] = 0;
					}
				}

				++x;
				if (x > COL - 4)
					x = COL - 4;

				
				gotoxy(x, y);

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if (block[i][j] == 1)
							tc[i + y][j + x] = 1;
						if (tc[i + y][j + x] == 2)
							tc[i + y][j + x] = 2;
					}
				}
				tc.UpdateMap();
			}
			else if (key == ESC) {
				gotoxy(0, 26);
				cout << "게임을 종료합니다." << endl;
				return 0;
			}

		}

		//점수 출력
		gotoxy(0, 25);
		std::cout << "Score: " << score << endl;

	}

	return 0;
}


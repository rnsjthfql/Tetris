#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

class Block
{
private:
	int*** block;
public:
	Block();
	~Block();

	int**& operator[](const int& idx) {
		return block[idx];
	}
};


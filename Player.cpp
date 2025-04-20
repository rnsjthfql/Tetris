#include "Player.h"

int Player::GetScore()
{
    return score;
}

void Player::SetScore(int num)
{
    score = num;
}

void Player::SetName(char n[10])
{
    strcpy_s(name, n);
}

char* Player::GetName()
{
    return name;
}

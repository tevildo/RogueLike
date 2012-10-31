#include "stdafx.h"
#include "Player.h"


Player::Player(void) : floor(1)
{
}


Player::~Player(void)
{
}

int Player::GetFloor()
{
	return floor;
}

void Player::Descend()
{
	floor++;
}

void Player::Ascend()
{
	if(floor > 1) floor--;
}
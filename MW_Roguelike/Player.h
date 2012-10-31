#pragma once

#include "Point.h"

class Player
{
public:
	Player(void);
	~Player(void);

	int GetFloor();

	void Descend();
	void Ascend();
	void North();
	void South();
	void East();
	void West();

private:
	int floor;
	Point position;
	int health;
	int maxHealth;
	int level;
};


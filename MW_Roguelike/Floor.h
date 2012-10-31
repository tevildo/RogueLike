#pragma once

#include <vector>
#include "Room.h"
#include "Corridor.h"
#include "Stairway.h"
#include "Monster.h"

class Floor
{
public:
	Floor(int width, 
		int height, 
		std::vector<Room> rooms,
		std::vector<Corridor> corridors);

	~Floor(void);

	void Animate(int newTurn);
	void Render();
private:
	int *floor;

	std::vector<Room> rooms;
	std::vector<Corridor> corridors;
	std::vector<Stairway> stairways;
	std::vector<Monster> monsters;

	int width;
	int height;
	int lastRenderedTurn;
};


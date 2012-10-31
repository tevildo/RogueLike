#pragma once

#include <vector>
#include <memory>

#include "Point.h"

class Floor;

class FloorFactory
{
public:
	FloorFactory(int width, int height, int roomCount, int corridorLength);
	~FloorFactory(void);

	/*stairsUp are the points where there must be stairs to the
	  upper floor as there are stairs down from there.
	  
	  playerPosition is the player location on this floor. If
	  the player is not on this floor then the position should
	  have negative x and/or y*/
	Floor *CreateFloor(std::vector<Point> stairsUp,
		Point playerPosition);

private:
	int width;
	int height;
	int roomCount;
	int corridorLength;
};


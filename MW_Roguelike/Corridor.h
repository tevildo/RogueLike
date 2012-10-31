#pragma once

#include <vector>
#include "Point.h"

class Room;

class Corridor
{
public:
	Corridor(void);
	~Corridor(void);

	void AddPoint(Point point);
	bool Intersects(const Room &other);
	bool Intersects(const Corridor &other);

//private:
	std::vector<Point> points;
};


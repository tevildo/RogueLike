#pragma once

#include "Point.h"

class Corridor;

class Room
{
public:
	Room(void);
	~Room(void);

	bool Intersects(const Room &other);
	bool Intersects(const Corridor &other);
	bool LineIntersectsLine(Point l1p1, Point l1p2,
		Point l2p1, Point l2p2);
	bool Contains(Point p);

	Point topLeft;
	Point bottomRight;
};


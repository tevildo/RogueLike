#include "stdafx.h"
#include "Corridor.h"


Corridor::Corridor(void)
{
}


Corridor::~Corridor(void)
{
}

void Corridor::AddPoint(Point point)
{
	this->points.push_back(point);
}

bool Corridor::Intersects(const Room &other)
{
	return false;
}

bool Corridor::Intersects(const Corridor &other)
{
	return false;
}
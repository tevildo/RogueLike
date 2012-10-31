#include "stdafx.h"
#include "Room.h"

#include "Corridor.h"

Room::Room(void)
{
}


Room::~Room(void)
{
}

bool Room::Intersects(const Room &other)
{
	if ((this->topLeft.X - 1) < other.bottomRight.X 
		&& (this->bottomRight.X + 1) > other.topLeft.X
		&& (this->topLeft.Y - 1) < other.bottomRight.Y
		&& (this->bottomRight.Y + 1) > other.topLeft.Y) return true;
	return false;
}

bool Room::Intersects(const Corridor &other)
{
	Room rOther;

	for(auto first = other.points.begin(), second = first + 1, end = other.points.end();
		second != end;
		first++, second++)
	{
		Point tl, br;
		if(first->X == second->X)
		{
			//is vertical
			if(first->Y < second->Y)
			{
				tl.X = first->X;
				tl.Y = first->Y;
				br.X = second->X;
				br.Y = second->Y;
			}
			else
			{
				tl.X = second->X;
				tl.Y = second->Y;
				br.X = first->X;
				br.Y = first->Y;
			}
		}
		else
		{
			//is horizontal
			if(first->X < second->X)
			{
				tl.X = first->X;
				tl.Y = first->Y;
				br.X = second->X;
				br.Y = second->Y;
			}
			else
			{
				tl.X = second->X;
				tl.Y = second->Y;
				br.X = first->X;
				br.Y = first->Y;
			}
		}

		if (this->topLeft.X < br.X 
			&& this->bottomRight.X >tl.X
			&& this->topLeft.Y < br.Y
			&& this->bottomRight.Y > tl.Y) return true;
	}
	return false;
}

bool Room::LineIntersectsLine(Point l1p1, Point l1p2, Point l2p1, Point l2p2)
{
	float q = (l1p1.Y - l2p1.Y) * (l2p2.X - l2p1.X) - (l1p1.X - l2p1.X) * (l2p2.Y - l2p1.Y);
	float d = (l1p2.X - l1p1.X) * (l2p2.Y - l2p1.Y) - (l1p2.Y - l1p1.Y) * (l2p2.X - l2p1.X);

	if( d == 0 )
	{
		return false;
	}

	float r = q / d;

	q = (l1p1.Y - l2p1.Y) * (l1p2.X - l1p1.X) - (l1p1.X - l2p1.X) * (l1p2.Y - l1p1.Y);
	float s = q / d;

	if( r < 0 || r > 1 || s < 0 || s > 1 )
	{
		return false;
	}

	return true;
}

bool Room::Contains(Point p)
{
	return p.X >= this->topLeft.X
		&& p.X <= this->bottomRight.X
		&& p.Y >= this->topLeft.Y
		&& p.Y <= this->bottomRight.Y;
}
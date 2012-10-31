#include "stdafx.h"
#include "FloorFactory.h"

#include <algorithm>

#include "Floor.h"
#include "Room.h"
#include "Corridor.h"

FloorFactory::FloorFactory(int width, int height, int roomCount, int corridorLength) : width(width), height(height), roomCount(roomCount), corridorLength(corridorLength)
{

}


FloorFactory::~FloorFactory(void)
{
}

Floor *FloorFactory::CreateFloor(std::vector<Point> stairsUp,
								 Point playerPosition)
{
	std::vector<Room> rooms;
	std::vector<Corridor> corridors;

	//create first room
	int roomWidth = 5 + (rand() % 5 - 3),
		roomHeight = 5 + (rand() & 5 - 3),
		roomX = rand() % width,
		roomY = rand() % height;

	if(roomX + roomWidth > width)
	{
		roomX -= roomWidth;
	}
	if(roomY + roomHeight > height)
	{
		roomY -= roomHeight;
	}

	Room room;
	room.topLeft.X = roomX;
	room.topLeft.Y = roomY;
	room.bottomRight.X = roomX + roomWidth;
	room.bottomRight.Y = roomY + roomHeight;

	rooms.push_back(room);

	//create more rooms
	for(int i = 1; i < roomCount; i++)
	{
		//first a corridor from an existing room or corridor - 20% will cause a second leg
		Corridor cor;
		int direction;
		Point end;

		bool fromRoom = true;//(bool)(rand() % 2);
		if(fromRoom)
		{
			room = rooms[rand() % rooms.size()];
			direction = rand() % 4; //0 = up, clockwise
			Point start;

			int length = rand() % corridorLength + 3;

			switch(direction)
			{
			case 0:
				start.Y = room.topLeft.Y - 1; //outside the room
				start.X = room.topLeft.X + (rand() % (room.bottomRight.X - room.topLeft.X));

				end.X = start.X;
				end.Y = start.Y - length;
				break;
			case 1:
				start.X = room.bottomRight.X + 1; 
				start.Y = room.topLeft.Y + (rand() % (room.bottomRight.Y - room.topLeft.Y));

				end.Y = start.Y;
				end.X = start.X + length;
				break;
			case 2:
				start.Y = room.bottomRight.Y + 1;
				start.X = room.topLeft.X + (rand() % (room.bottomRight.X - room.topLeft.X));

				end.X = start.X;
				end.Y = start.Y + length;
				break;
			case 3:
				start.X = room.topLeft.X - 1;
				start.Y = room.topLeft.Y + (rand() % (room.bottomRight.Y - room.topLeft.Y));

				end.Y = start.Y;
				end.X = start.X - length;
				break;
			}

			cor.AddPoint(start);
			cor.AddPoint(end);
		}
		else //not implemented, run from corridor
		{
		}

		//while(rand() % 5 == 0) //20% of the time, add more points
		//{
		//}

		//then a room at the end of that corridor
		roomWidth = 5 + (rand() % 5 - 3);
		roomHeight = 5 + (rand() & 5 - 3);

		switch(direction)
		{
		case 0:
			// - 1 from end Y
			// bottom right X is end X + rand() % roomwidth
			room.bottomRight.Y = end.Y - 1;
			room.bottomRight.X = end.X + (rand() & roomWidth);
			room.topLeft.X = room.bottomRight.X - roomWidth;
			room.topLeft.Y = room.bottomRight.Y - roomHeight;
			break;
		case 1:
			// + 1 to end X
			// top left Y is endY - rand() % roomHeight
			room.topLeft.X = end.X + 1;
			room.topLeft.Y = end.Y - (rand() % roomHeight);
			room.bottomRight.X = room.topLeft.X + roomWidth;
			room.bottomRight.Y = room.topLeft.Y + roomHeight;
			break;
		case 2:
			// + 1 from end Y
			// top left X is end X - rand() % roomwidth
			room.topLeft.Y = end.Y + 1;
			room.topLeft.X = end.X - (rand() & roomWidth);
			room.bottomRight.X = room.topLeft.X + roomWidth;
			room.bottomRight.Y = room.topLeft.Y + roomHeight;
			break;
		case 3:
			// - 1 to end X
			// bottom right Y is endY + rand() % roomHeight
			room.bottomRight.X = end.X - 1;
			room.bottomRight.Y = end.Y + (rand() % roomHeight);
			room.topLeft.X = room.bottomRight.X - roomWidth;
			room.topLeft.Y = room.bottomRight.Y - roomHeight;
			break;
		}

		//check is inside floor
		if(room.topLeft.X < 0
			|| room.topLeft.Y < 0
			|| room.bottomRight.X > width
			|| room.bottomRight.Y > height) 
		{
			i--;
			continue;
		}

		//check does not intersect any other rooms or corridors
		bool intersects = false;

		for(auto itr = rooms.begin(), end = rooms.end(); itr != end; ++itr)
		{
			if(room.Intersects(*itr) || cor.Intersects(*itr))
			{
				intersects=true;
				break;
			}
		}
		if(!intersects) 
		{
			for(auto itr = corridors.begin(), end = corridors.end(); itr != end; ++itr)
			{
				if(room.Intersects(*itr) || cor.Intersects(*itr))
				{
					intersects = true;
					break;
				}
			}
		}

		if(intersects)
		{
			i--;
			continue;
		}

		//add both room and cor
		rooms.push_back(room);
		corridors.push_back(cor);
	}

	return new Floor(width,
		height,
		rooms,
		corridors);
	
}
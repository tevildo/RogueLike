#include "stdafx.h"

#include <iostream>
#include <string.h>

#include "Floor.h"

#include "TileTypes.h"

Floor::Floor(int width,
			 int height,
			 std::vector<Room> rooms,
			 std::vector<Corridor> corridors) : width(width), height(height), lastRenderedTurn(1)
{
	floor = new int[width * height];
	//for(int i = 0; i < width * height; i++) floor[i] = TileType::wall;
	memset(floor, TileType::wall, width * height * 4);

	for(auto itr = rooms.begin(), end = rooms.end();
		itr != end;
		++itr)
	{
		for(int x = itr->topLeft.X - 1;
			x < itr->bottomRight.X;
			x++)
		{
			for(int y = itr->topLeft.Y - 1;
				y < itr->bottomRight.Y;
				y++)
			{
				int idx = (y * width) + x;
				floor[idx] = TileType::empty;
			}
		}
	}

	for(auto itr = corridors.begin(), end = corridors.end();
		itr != end;
		++itr)
	{
		for(auto first = itr->points.begin(), second = first+1, endPoint = itr->points.end();
			second != endPoint;
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

			for(int x = tl.X - 1;
				x < br.X;
				x++)
			{
				for(int y = tl.Y - 1;
					y < br.Y;
					y++)
				{
					int idx = (y * width) + x;
					floor[idx] = TileType::empty;
				}
			}
		}


	}
}


Floor::~Floor(void)
{
}

void Floor::Animate(int newTurn)
{
	for(int i = lastRenderedTurn; i < newTurn; i++)
	{
		//TODO: move monsters
	}
}

void Floor::Render()
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			switch(floor[(y * width) + x])
			{
			case TileType::empty:
				std::cout << " ";
				break;
			case TileType::wall:
				std::cout << "#";
				break;
			}

		}
		std::cout << std::endl;
	}
}

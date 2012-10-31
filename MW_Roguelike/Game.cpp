#include "stdafx.h"
#include "Game.h"

#include "FloorFactory.h"

Game::Game(std::shared_ptr<FloorFactory> floorFact) : turn(0), player(nullptr), floorFactory(floorFact)
{
	
}


Game::~Game(void)
{
}

void Game::SetPlayer(std::shared_ptr<Player> player)
{
	this->player = player;
}

int Game::IncrementTurn()
{
	return ++turn;
}

void Game::Animate()
{
	//check that floor exists
	int currentFloor = player->GetFloor();
	std::vector<Point> stairsUp;
	Point playerPos;
	playerPos.X = -1;
	playerPos.Y = -1;

	while((int)floors.size() < currentFloor)
	{
		//use FloorFactory to create a floor
		//it will need to know where stairs down from above are
		//as well as player position if within this floor
		floors.push_back(*floorFactory->CreateFloor(stairsUp,
			playerPos));
	}

	floors[currentFloor - 1].Animate(turn);
}

void Game::Render()
{
	floors[player->GetFloor() - 1].Render();

}
#pragma once

#include <vector>
#include <memory>

#include "Floor.h"

class Player;
class FloorFactory;

class Game
{
public:
	Game(std::shared_ptr<FloorFactory>);
	~Game(void);

	void SetPlayer(std::shared_ptr<Player>);
	int IncrementTurn();
	void Animate();
	void Render();
	//void MoveMonstersOnCurrentFloor();
	//void CheckFloorExists();

private:
	int turn;
	int maxDepth;
	std::shared_ptr<Player> player;
	std::vector<Floor> floors;
	std::shared_ptr<FloorFactory> floorFactory;
	
};


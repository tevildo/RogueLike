// MW_Roguelike.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <memory>

#include "Game.h"
#include "Player.h"
#include "FloorFactory.h"

bool run = true;

int main(int argc, char* argv[])
{
	//setup
	srand( time(NULL) );

	//create the 'game' and player
	std::shared_ptr<FloorFactory> floorFact(new FloorFactory(50, 50, 7, 5));
	std::shared_ptr<Game> game(new Game(floorFact));
	std::shared_ptr<Player> player(new Player());
	game->SetPlayer(player);

	//main loop
	while(run)
	{
		//compute - increment turn, handle enemy movement (if any), generate new floor if moved
		game->IncrementTurn();
		game->Animate();

		//render
		game->Render();

		//input - blocking, as we're turn based
		int c = 0;
		while(!(c == 62 || c == 60))
		{
			c = fgetc(stdin);

			if(c == 62) player->Descend();
			else if(c == 60) player->Ascend();
		}
	}
	return 0;
}


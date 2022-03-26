#pragma warning(default:4265)
#include "game_engine.h"
#include <iostream>
#include <ctime>
#include <cstdlib> 
/*----------
	main c++ class for POGame
	starts the main program
----------*/
game_engine *gameInstance = nullptr;

int main(int argc, char *argv[])
{
	printf("STARTING POGame\n\n\n");

	srand((int)time(NULL));

	// create instance of the game engine and init it
	gameInstance = new game_engine();

	if (!gameInstance->init())
	{
		std::cin.get();
		return 1;
	}

	// start the game engine
	gameInstance->run();

	// (only ran after game is closed)
	// stop game engine
	gameInstance->stop();

	std::cin.get();

	return 0;
}
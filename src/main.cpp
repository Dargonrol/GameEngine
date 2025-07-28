#include <iostream>
#include <raylib.h>

#include "Game.h"

int main()
{
	Game game;
	game.init();
	game.run();
	game.shutdown();

	return 0;
}

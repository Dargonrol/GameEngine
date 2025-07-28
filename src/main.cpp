#include <iostream>
#include <raylib.h>

#include "Game.h"

int main()
{
	Game& game = Game::getInstance();
	game.init();
	game.run();
	game.shutdown();

	return 0;
}

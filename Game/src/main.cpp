#include <iostream>
#include <raylib.h>

#include "Game.h"

int main()
{
	Core::Game& game = Core::Game::getInstance();
	game.init();
	game.run();
	game.shutdown();

	return 0;
}

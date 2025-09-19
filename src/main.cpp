#include <iostream>
#include <raylib.h>

#include "Game.h"

int main()
{
	Pong::Game& game = Pong::Game::getInstance();
	game.init();
	game.run();
	game.shutdown();

	return 0;
}

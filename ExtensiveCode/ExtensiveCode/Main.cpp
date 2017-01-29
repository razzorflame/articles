#include "Include/Game.hpp"

int main()
{
	auto game = new CGame();

	game->Run();

	delete game;

	return 0;
}


#include "Include/Game.hpp"

int main()
{
	auto &game = CGame::Instance();

	game.Run();

	return 0;
}


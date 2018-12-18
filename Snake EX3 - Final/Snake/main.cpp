#include "MainMenu.h"
#include "Game.h"

void main()
{
	Game game;
	bool run = true;
	printBigSnake();
	game.setActiveMissions(loadMissions(run, game.getActiveMissionCount()));
	MainMenu(1,run, game);
}
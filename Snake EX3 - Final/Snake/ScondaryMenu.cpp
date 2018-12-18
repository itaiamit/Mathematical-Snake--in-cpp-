#include "Game.h"
#include "ScondaryMenu.h"
#include "Board.h"
#include "MainMenu.h"
#include "Missions.h"
#include <iostream>
using namespace std;

void SecondaryMenu(Missions& mission, Board& board, bool& go, bool& run, bool& firstTurn, Game& game)
{
	int choice;
	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW | FOREGROUND_INTENSITY);
	cout << "                         What would you like to do?                            " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN | FOREGROUND_INTENSITY);
	cout << "1)Exit 2)Menu 3)Continue 4)Restart Mission 5)New Mission 6)New Game 7)Replay ";
	gotoxy(78, 1);
	cout << "  ";
	gotoxy(78, 1);
	cin >> choice;

	while (choice != EXIT && choice != MAIN_MENU && choice != CONTINUE && choice != RESTART_MISSION && choice != NEW_MISSION && choice != NEW_GAME && choice != REPLAY)
		cin >> choice;

	switch (choice)
	{
	//Exit
	case 1:
		ExitGame(0,go);
		if(!go)
			run = false;
		break;

	//Main Menu
	case 2:
		PlaySound(TEXT("sfx_sounds_button3.wav"), NULL, SND_SYNC | SND_NODEFAULT);
		go = false;
		break;

	//Continue
	case 3:
		PlaySound(TEXT("sfx_sounds_button3.wav"), NULL, SND_SYNC | SND_NODEFAULT);
		break;

	//Restart mission
	case 4:
		PlaySound(TEXT("sfx_sounds_button3.wav"), NULL, SND_SYNC | SND_NODEFAULT);
		game.getNums().resetAll();
		game.resetBullets();
		game.resetCreatures();
		board.clearSnakesBoard();
		game.setCreaturesOnBoard();
		break;

	//New mission
	case 5:
		PlaySound(TEXT("sfx_sounds_button3.wav"), NULL, SND_SYNC | SND_NODEFAULT);
		mission.setCurrMission(game.getActiveMissions() ,game.getActiveMissionCount());
		game.resetBullets();
		game.resetCreatures();
		game.setCreaturesOnBoard();
		mission.setMission();
		break;

	//New game
	case 6:
		PlaySound(TEXT("sfx_sounds_button3.wav"), NULL, SND_SYNC | SND_NODEFAULT);
		firstTurn = true;
		game.resetGame();
		break;

	//Replay
	case 7:
		PlaySound(TEXT("sfx_sounds_button3.wav"), NULL, SND_SYNC | SND_NODEFAULT);
		game.firstReplayActs(firstTurn);
		break;
	}
}

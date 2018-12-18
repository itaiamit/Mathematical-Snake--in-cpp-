#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_
#include "Utilities.h"
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <conio.h>
#include "Colors.h"
#include "Game.h"
using namespace std;

enum {INSTRUCTIONS = 1, NEW_GAME_MAIN = 2, EXIT_MAIN = 9};
void printBigSnake();
void MainMenu(bool MainOrSecond,bool& run, Game& game); // true is main, false is scondary
void Instructions();
void GoodLuck();
void ExitGame(bool MainOrSecondary,bool& go); // true is main, false is scondary

#endif // !_MAIN_MENU_H_

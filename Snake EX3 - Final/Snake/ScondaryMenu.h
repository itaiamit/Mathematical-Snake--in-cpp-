#ifndef _SECONDARY_MENU_H_
#define _SECONDARY_MENU_H_
#include "Utilities.h"

enum {EXIT = 1, MAIN_MENU, CONTINUE, RESTART_MISSION, NEW_MISSION, NEW_GAME, REPLAY};
void SecondaryMenu(Missions& mission, Board& board, bool& go, bool& run, bool& firstTurn, Game& game);

#endif // !_SECONDARY_MENU_H_

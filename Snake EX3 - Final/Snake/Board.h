#ifndef _BOARD_H_
#define	_BOARD_H_
#include "Missions.h"
#include "Utilities.h"

enum { ROWS = 25, COLS = 81 };

class Missions;

class Board
{
	char board[ROWS][COLS];

public:
	void setBoard();
	void displayBoard();
	char getDigit(int x, int y);
	bool isSnakesChar(int x, int y);
	void setDigit(int x, int y, char c) { board[x][y] = c; }
	void getBoard(char temp[ROWS][COLS]) { temp = board; }
	void clearSnakesBoard();
	bool isSpace(int x, int y);
	char getChar(int x, int y) { return board[x][y]; }
};
#endif // !_BOARD_H_
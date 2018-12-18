#include "Board.h"
#include <string.h>
#include <iostream>
using namespace std;

// Sets game board (walls, and spaces inside).
void Board::setBoard()
{
	int x, y, i, j;

	// Top and down walls
	for (x = 0; x < COLS - 1; x++)
	{
		board[2][x] = '+';
		board[ROWS - 1][x] = '+';
	}

	// Left and right walls
	for (y = 3; y < ROWS - 1; y++)
	{
		board[y][0] = '+';
		board[y][COLS - 2] = '+';
	}

	// Filling the board with spaces.
	for (i = 3; i < ROWS - 1; i++)
		for (j = 1; j < COLS - 2; j++)
			board[i][j] = ' ';

	for (i = 2; i < ROWS; i++)
		board[i][COLS - 1] = '\0';
}

void Board::displayBoard()
{
	gotoxy(0, 2);

	for (int i = 2; i < ROWS; ++i)
		for (int j = 0; j < COLS - 1; j++)
		{
			if (i < 2)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREY);

			cout << board[i][j];
		}
}

// Returns the character in (x,y).
char Board::getDigit(int x, int y)
{
	char c = board[x][y];
	if ((c == ' ') || (c == '@') || (c == '#') || (c == '+') || (c == '*')
		|| (c == '!') || (c == '$') || (c == '%'))
		return -1;

	return c;
}

// Checks if in (x,y) there is a snake.
bool Board::isSnakesChar(int x, int y)
{
	char c = board[x][y];

	if (c == '@' || c == '#')
		return true;

	return false;
}

// Clears game board.
void Board::clearSnakesBoard()
{
	for (int i = 1; i < COLS - 2; i++)
		for (int j = 3; j < ROWS -1; j++)
		{
			board[j][i] = ' ';
			gotoxy(i, j);
			cout << ' ';
		}
}

bool Board::isSpace(int x, int y)
{
	if (board[x][y] == ' ')
		return true;

	return false;
}

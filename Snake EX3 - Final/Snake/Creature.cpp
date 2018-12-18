#include "Creature.h"

Creature::Creature(char _sign, Point _point, Direction _dir, Color _color, bool _canPass)
{
	resetCreature(_sign, _point, _dir, _color, _canPass);
}

void Creature::move(Board & board)
{
	point.draw(' ');
	board.setDigit(point.getY(), point.getX(), ' ');
	moveImpl(board);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | FOREGROUND_INTENSITY);
	point.draw(sign);
	updateCreatureOnBoard(board, sign);
}

void Creature::resetCreature(char _sign, Point _point, Direction _dir, Color _color, bool _canPass)
{
	sign = _sign;
	point = _point;
	dir = _dir;
	point.changeDir(dir);
	color = _color;
	canPass = _canPass;
	disappeared = false;
}

void Creature::printCreature(Board & board)
{
	board.setDigit(point.getY(), point.getX(), sign);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | FOREGROUND_INTENSITY);
	point.draw(sign);
}

void rowFlies::moveImpl(Board& board)
{
	if (point.getDirX() == -1 && point.getX() < min_x + 1) // LEFT
	{
		if (canPass)
			point.setX(max_x);
		else
		{
			dir = reverseDir(dir);
			point.changeDir(dir);
		}
	}

	else if (point.getDirX() == 1 && point.getX() > max_x - 1) // RIGHT
	{
		if (canPass)
			point.setX(min_x);
		else
		{
			dir = reverseDir(dir);
			point.changeDir(dir);
		}
	}

	else
		point.setX((point.getX() + point.getDirX() + max_x + 1) % (max_x + 1)); // ELSE

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | FOREGROUND_INTENSITY);
	point.draw(sign);
	updateCreatureOnBoard(board, sign);
}

void colFlies::moveImpl(Board & board)
{
	if (point.getDirY() == -1 && point.getY() < min_y + 1) // UP
	{
		if (canPass)
			point.setY(max_y);
		else
		{
			dir = reverseDir(dir);
			point.changeDir(dir);
		}
	}

	else if (point.getDirY() == 1 && point.getY() > max_y - 1) // DOWN
	{
		if (canPass)
			point.setY(min_y);
		else
		{
			dir = reverseDir(dir);
			point.changeDir(dir);
		}
	}

	else
		point.setY((point.getY() + point.getDirY() + max_y + 1) % (max_y + 1)); // ELSE

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | FOREGROUND_INTENSITY);
	point.draw(sign);
	updateCreatureOnBoard(board, sign);
}

void numEater::moveImpl(Board & board)
{
	// X moves
	{
		if (point.getDirX() == -1 && point.getX() < min_x + 1) // LEFT
			point.setX(max_x);

		else if (point.getDirX() == 1 && point.getX() > max_x - 1) // RIGHT
			point.setX(min_x);

		else
			point.setX((point.getX() + point.getDirX() + max_x + 1) % (max_x + 1)); // ELSE
	}

	// Y moves
	{
		if (point.getDirY() == -1 && point.getY() < min_y + 1) // UP
			point.setY(max_y);

		else if (point.getDirY() == 1 && point.getY() > max_y - 1) // DOWN
			point.setY(min_y);

		else
			point.setY((point.getY() + point.getDirY() + max_y + 1) % (max_y + 1)); // ELSE
	}

	updateCreatureOnBoard(board, sign);
}

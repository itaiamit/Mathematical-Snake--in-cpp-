#include "Point.h"

void Point::operator=(const Point & other)
{
	x = other.x;
	y = other.y;
	dir_x = other.dir_x;
	dir_y = other.dir_y;
}

bool Point::operator!=(const Point & other)
{
	if (x != other.x || y != other.y)
		return true;

	return false;
}

bool Point::operator==(const Point & other)
{
	if (x == other.x && y == other.y)
		return true;

	return false;
}

//move limits
void Point::moveImpl()
{
	// For the y
	{
		if (dir_y == -1 && y < min_y + 1) // UP
			y = max_y;

		else if (dir_y == 1 && y > max_y - 1) // DOWN
			y = min_y;

		else
			y = (y + dir_y + max_y + 1) % (max_y + 1); // ELSE
	}
	// For the x
	{
		if (dir_x == -1 && x < min_x + 1) // LEFT
			x = max_x;

		else if (dir_x == 1 && x > max_x - 1) // RIGHT
			x = min_x;

		else
			x = (x + dir_x + max_x + 1) % (max_x + 1); // ELSE
	}
}

// Changes snake's direction.
void Point::changeDir(Direction dir)
{
	switch (dir)
	{
	case Direction::LEFT:
		dir_x = -1;
		dir_y = 0;
		break;
	case Direction::RIGHT:
		dir_x = 1;
		dir_y = 0;
		break;
	case Direction::UP:
		dir_x = 0;
		dir_y = -1;
		break;
	case Direction::DOWN:
		dir_x = 0;
		dir_y = 1;
		break;
	}
}

Direction Point::getDir()
{
	if (dir_x == -1 && dir_y == 0)
		return LEFT;

	else if (dir_x == 1 && dir_y == 0)
		return RIGHT;

	else if (dir_x == 0 && dir_y == -1)
		return UP;

	else if (dir_x == 0 && dir_y == 1)
		return DOWN;
}
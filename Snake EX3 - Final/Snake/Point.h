
#ifndef _POINT_H_
#define _POINT_H_

#include "Utilities.h"
#include <iostream>
#include "Direction.h"

using namespace std;
enum { min_x = 1, max_x = 78, min_y = 3, max_y = 23 };

class Point
{
	int x;
	int y;
	int dir_x = 1;
	int dir_y = 0;

public:
	Point(int x1 = 1, int y1 = 1, int dir_x1 = 1, int dir_y1 = 0)
	{
		x = x1;
		y = y1;
		dir_x = dir_x1;
		dir_y = dir_y1;
	}
	void operator=(const Point& other);
	bool operator!=(const Point & other);
	bool operator==(const Point & other);
	void moveImpl();
	int getX() const { return x; }
	int getY() const { return y; }
	int getDirX() const { return dir_x; }
	int getDirY() const { return dir_y; }
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
	void setDirX(int _dirX) { dir_x = _dirX; }
	void setDirY(int _dirY) { dir_y = _dirY; }

	// Prints a character on console screen.
	void draw(char c = '*')
	{
		gotoxy(x, y);
		cout << c << endl;
	}
	void changeDir(Direction dir);
	Direction getDir();
	void move(Direction dir)
	{
		changeDir(dir);
		moveImpl();
	}
};

#endif
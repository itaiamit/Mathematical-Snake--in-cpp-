#ifndef _BULLET_H_
#define _BULLET_H_

#include "Board.h"
#include "Utilities.h"

const char BULLET_SIGN = '*';

class Bullet
{
	Point position;
	Direction dir;
	Color color;
	friend class Snake;

public:
	void moveBullet(Board& board);
	void updateBulletOnBoard(Board& board) {board.setDigit(position.getY(), position.getX(), BULLET_SIGN);}
	void setBullet(Point pos = { -1, -1 }, Direction _dir = UP);
	Color getColor() { return color; }
	Point& getPosition() { return position; }
	Direction getDirection() { return dir; }
	string getType() { return "bullet"; }
};

#endif // !_BULLET_H_

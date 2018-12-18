#include "Bullet.h"

// Bullet's moves.
void Bullet::moveBullet(Board& board)
{
	position.draw(' ');
	board.setDigit(position.getY(), position.getX(), ' ');
	position.moveImpl();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | FOREGROUND_INTENSITY);
	position.draw(BULLET_SIGN);
	updateBulletOnBoard(board);
}

// Set bullet.
void Bullet::setBullet(Point pos, Direction _dir)
{
	position = pos;
	dir = _dir;
}




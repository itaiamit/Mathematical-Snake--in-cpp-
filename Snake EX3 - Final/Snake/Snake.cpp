#include "Snake.h"

Snake::Snake(const Point& head, char c1, int length, Direction dir, Color _color, char _shootKey)
{
	resetSnake(head, c1, length, dir, _color, _shootKey);
}

void Snake::resetSnake(const Point & head, char c1, int length, Direction dir, Color _color, char _shootKey)
{
	c = c1;
	direction = reverseDir(dir);
	color = _color;
	body[0] = head;
	currLen = length;
	for (int i = 1; i < length; ++i)
	{
		body[i] = body[i - 1];
		body[i].move(direction);
	}

	for (int i = 0; i < MAX_BULLETS; i++)
		bullet[i].color = _color;

	top = 0;
	direction = dir;
	shootKey = _shootKey;
	ammunition = MAX_BULLETS;
	pauseSnake = 0;
}

// Sets direction keys.
void Snake::setKeys(char keyLeft, char keyRight, char keyUp, char keyDown) {
	dirKeys[Direction::LEFT] = keyLeft;
	dirKeys[Direction::RIGHT] = keyRight;
	dirKeys[Direction::UP] = keyUp;
	dirKeys[Direction::DOWN] = keyDown;
}

void Snake::changeDir(char keyPressed)
{
	for (const auto& key : dirKeys)
		if (key == keyPressed)
			direction = (Direction)(&key - dirKeys);
}

// Snake's moves.
Point Snake::move(char keyPressed)
{
	body[currLen - 1].draw(' ');

	for (int i = currLen - 1; i > 0; --i)
		body[i] = body[i - 1];

	body[0].move(direction);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | FOREGROUND_INTENSITY);
	body[0].draw(c);

	return body[0];
}

// Making the snake disappear from screen and board after was hit by a bullet.
void Snake::disappear(Board& board)
{
	for (int i = currLen - 1; i >= 0; i--)
	{
		body[i].draw(' ');
		board.setDigit(body[i].getY(), body[i].getX(), ' ');
		body[i].setX(-1);
		body[i].setY(-1);
	}
}

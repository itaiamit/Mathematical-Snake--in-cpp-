#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Utilities.h"
#include "Point.h"
#include "Direction.h"
#include <Windows.h>
#include "Colors.h"
#include "Bullet.h"

enum { MAX_BODY_SIZE = 15, KEYS = 4 };
enum {MAX_BULLETS = 5};

class Snake
{
	Color color;
	Point body[MAX_BODY_SIZE] = {};
	char c;
	Direction direction;
	char dirKeys[KEYS]; // the keys for the four possible directions
	Bullet bullet[MAX_BULLETS];
	char shootKey;
	int ammunition;
	int top;
	int pauseSnake; // Controls for how long the snake will be disappeared if was hitten by a bullet.

public:
	int currLen;
	Snake(const Point& head, char c1, int length, Direction dir, Color _color, char _shootKey);
	void resetSnake(const Point& head, char c1, int length, Direction dir, Color _color, char _shootKey);
	void setKeys(char keyLeft, char keyRight, char keyUp, char keyDown);
	void changeDir(char keyPressed);
	Point move(char keyPressed);
	char getChar() const { return c; }
	Direction getDirection() { return direction; }
	void updateSnakeSize(int& length) { currLen = length + 1; }
	Point& getSnakesBodyPart(int i) { return body[i]; }
	Color getColor() { return color; }
	char getShootKey() { return shootKey; }
	int getAmmunition() { return ammunition; }
	void updateAmmunition(int update) { ammunition = update; }
	Bullet& getBullet(int i) { return bullet[i]; }
	void setFirstBullet(int i) { bullet[i].setBullet(body[0], direction); }
	int& getTop() { return top; }
	void setTop(int _top) { top = _top; }
	void disappear(Board& board);
	int getPaused() { return pauseSnake; }
	void setPaused(int update) { pauseSnake = update; }
	int getSnakeIndex() { return (c == '@')? 0 : 1; }
	void setDirestion(Direction _dir) { direction = _dir; }
};

#endif
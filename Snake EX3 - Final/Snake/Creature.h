#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "Snake.h"
#include "Board.h"

class Creature
{
protected:
	char sign;
	Point point;
	Direction dir;
	Color color;
	bool canPass;
	bool disappeared;

public:	
	Creature(char _sign, Point _point, Direction _dir, Color _color, bool _canPass);
	void move(Board& board);
	virtual void moveImpl(Board& board) = 0;
	void resetCreature(char _sign, Point _point, Direction _dir, Color _color, bool _canPass);
	void printCreature(Board& board);
	Point& getPosition() { return point; }
	bool getDisappeared() { return disappeared; }
	void setDisappeared(bool _disappeared) { disappeared = _disappeared; }
	void updateCreatureOnBoard(Board& board, char sign) { board.setDigit(point.getY(), point.getX(), sign); }
	void setDirection(Direction _dir) { dir = _dir; }
	virtual string getType() = 0;
	char getSign() { return sign; }
	Color getColor() { return color; }
};

class rowFlies : public Creature
{
public:
	rowFlies(Point _point, Direction _dir, bool _canPass) : Creature('!', _point, _dir, LIGHTRED, _canPass) {}
	virtual void moveImpl(Board& board);
	virtual string getType() { return "rowFlies"; }
};

class colFlies : public Creature
{
public:
	colFlies(Point _point, Direction _dir, bool _canPass) : Creature('$', _point, _dir, GREEN, _canPass) {}
	virtual void moveImpl(Board& board);
	virtual string getType() { return "colFlies"; }
};

class numEater : public Creature
{
	Point destination;
	unsigned int distance; // To destination
	Direction dirY; // The numEater yDirection

public:
	numEater(Point _point, Direction _dir, bool _canPass = true) : Creature('%', _point, _dir, YELLOW, _canPass) { destination =  Point(-1, -1); distance = max_x + max_y; dirY = UP; }
	virtual void moveImpl(Board& board);
	unsigned int getDistance() { return distance; }
	void setDistance(unsigned int _distance) { distance = _distance; }
	Point getDestination() { return destination; }
	void setDestination(Point _destination) { destination = _destination; }
	virtual string getType() { return "numEater"; }
	void setDirY(Direction _dirY) { dirY = _dirY; }
	Direction getDirY() { return dirY; }
};

#endif // !_CREATURE_H_

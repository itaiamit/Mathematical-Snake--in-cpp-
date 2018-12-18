#ifndef _NUMBERS_H_
#define _NUMBERS_H_
#include "Missions.h"
#include "Board.h"
class Board;
class Missions;

struct Numbers
{
	int num;
	int x;
	int y;
	bool goodNum = false;
};

enum { MAX_NUMS_ON_SCREEN = 60 };
class NumsOnScreen
{
	Numbers number[MAX_NUMS_ON_SCREEN];
	int howManyOnScreen = 0;
	int howManyGoods = 0;

public:
	NumsOnScreen();
	void resetNum(Numbers* number, int index);
	void resetAll();
	void resetHowMany() { howManyOnScreen /= 2; }
	int getHowMany() { return howManyOnScreen; }
	int getNumber(const Point& pos, Board& board, Point& leftDigPos);
	void setNum(Numbers* number, int index, int _num, int _x, int _y, bool _goodNum);
	Numbers* getNumbersArray() { return number; }
	Numbers getNumberByIndex(int i) { return number[i]; }
	void checkAndShowGoodNumbers(Numbers* number);
	void setGoodNumbers(Missions mission);
	void updateArray(int newSize, Point& leftDigPos);
	void deleteNumberFromArray(Point& leftDigPos);
	void numSwap(Numbers& num1, Numbers& num2);
	void printNewArray(Board& board);
	int getNumLength(const Board& board, int index, string* strNum);
	void numbersLottery(Board & board, const Point * head, int missionNumber, int * retNum, int * _x, int * _y);
	bool checkAroundTheNumber(Point head, Board & board, int x, int y);
	Point getRandomNumFromArray();
	int getNumberByPosition(Point pos);
	bool getIsGoodNum(int i) { return number[i].goodNum; }
	int getX(int i) { return number[i].x; }
	int getY(int i) { return number[i].y; }
	bool isDigit(char c);
	int generateNumber();
};

#endif // !_NUMBERS_H_
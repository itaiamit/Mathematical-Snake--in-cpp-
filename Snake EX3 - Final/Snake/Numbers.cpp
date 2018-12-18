#include "Numbers.h"
#include <sstream>
#include <string>

NumsOnScreen::NumsOnScreen()
{
	for (int i = 0; i < MAX_NUMS_ON_SCREEN; i++)
	{
		number[i].num = -1;
		number[i].x = 0;
		number[i].y = 0;
		number[i].goodNum = false;
	}

	howManyOnScreen = 0;
	howManyGoods = 0;
}

// Resets a number in the "NumsOnScreen" array in a specific index.
void NumsOnScreen::resetNum(Numbers* number, int index)
{
	number[index].num = -1;
	number[index].x = 0;
	number[index].y = 0;
	number[index].goodNum = false;
}

void NumsOnScreen::resetAll()
{
	for (int i = 0; i < howManyOnScreen; i++)
	{
		number[i].num = -1;
		number[i].x = 0;
		number[i].y = 0;
		number[i].goodNum = false;
	}

	howManyOnScreen = 0;
	howManyGoods = 0;
}

// Returns the number on the board the snake stucked into it.
int NumsOnScreen::getNumber(const Point & pos, Board& board, Point& leftDigPos)
{
	int x = pos.getX();
	int y = pos.getY();
	int num = 0, digit, start, end;
	start = end = x;

	while (x > 0 && board.getDigit(y, end) != -1)
	{
		if (x == end && end - 1 >= 1 && (board.getDigit(y, end - 1) == ' ' || board.getDigit(y, end - 1) == '+'))
			break;
		end--;
	}
	++end;

	leftDigPos.setX(end);
	leftDigPos.setY(y);

	while (x < COLS - 2 && board.getDigit(y, start) != -1)
	{
		if (x == start && start + 1 < COLS - 2 && (board.getDigit(y, start + 1) == ' ' || board.getDigit(y, start + 1) == '+'))
			break;
		start++;
	}
	--start;

	digit = board.getDigit(y, end) - '0';
	while (start >= end && digit != -1)
	{
		num = num * 10 + digit;
		board.setDigit(y, end, ' ');
		gotoxy(end, y);
		cout << ' ';
		end++;
		digit = board.getDigit(y, end) - '0';
	}

	return num; 
}

// Sets a number in "NumsOnScreen" array.
void NumsOnScreen::setNum(Numbers* number, int index, int _num, int _x, int _y, bool _goodNum)
{
	number[index].num = _num; // Sets a number
	number[index].x = _x;	// x cordination
	number[index].y = _y;	// y cordination
	number[index].goodNum = _goodNum; // if it's a good number for the current mission

	if (_goodNum)
		howManyGoods++;

	howManyOnScreen++;
}

// Checks and shows on screen the good numbers of the ended mission.
void NumsOnScreen::checkAndShowGoodNumbers(Numbers * number)
{
	gotoxy(1, 3);
	if (howManyGoods == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED | FOREGROUND_INTENSITY);
		cout << "There were NO matching numbers in this mission.    ";
		Sleep(1500);
	}

	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN | FOREGROUND_INTENSITY);
		cout << "There were matching numbers for this mission: ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW | FOREGROUND_INTENSITY);
		gotoxy(1, 4);
		for (int i = 0; i < howManyOnScreen; i++)
			if (number[i].goodNum)
				cout << number[i].num << ", ";

		cout << "\b\b.";
		Sleep(3000);
	}
}

// Updates all numbers (if they are good for the current mission).
void NumsOnScreen::setGoodNumbers(Missions mission)
{
	int goods = 0;

	for (int i = 0; i < howManyOnScreen; i++)
		if (mission.checkNumber(number[i].num))
		{
			number[i].goodNum = true;
			goods++;
		}
		else
			number[i].goodNum = false;

	howManyGoods = goods;
}

// Shrinks "NumsOnScreen" array (randomally) by half.
void NumsOnScreen::updateArray(int newSize, Point& leftDigPos)
{
	int index;

	deleteNumberFromArray(leftDigPos);

	for (int i = 0; i < newSize; i++)
	{
		index = rand() % howManyOnScreen;
		numSwap(number[index], number[howManyOnScreen - 1]);
		resetNum(number, howManyOnScreen - 1);
		howManyOnScreen--;
	}
}

void NumsOnScreen::deleteNumberFromArray(Point & leftDigPos)
{
	for (int i = 0; i < howManyOnScreen; i++)
		if (number[i].x == leftDigPos.getX() && number[i].y == leftDigPos.getY())
		{
			numSwap(number[i], number[howManyOnScreen - 1]);
			resetNum(number, howManyOnScreen - 1);
			howManyOnScreen--;
			break;
		}
}

void NumsOnScreen::numSwap(Numbers & num1, Numbers & num2)
{
	Numbers temp;
	temp = num1;
	num1 = num2;
	num2 = temp;
}

// Prints the new shrinked array on board.
void NumsOnScreen::printNewArray(Board& board)
{
	int numLength, digit = 0;
	string strNum;

	for (int i = 0; i < howManyOnScreen; i++)
	{
		numLength = getNumLength(board, i, &strNum);
		for (int j = number[i].x; j < number[i].x + numLength; j++)
		{
			board.setDigit(number[i].y, j, strNum.at(digit));
			digit++;
		}

		gotoxy(number[i].x, number[i].y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		cout << strNum;
		digit = 0;
	}
}

int NumsOnScreen::getNumLength(const Board& board, int index, string* strNum)
{
	int numLength;
	string str = intToString(number[index].num);

	numLength = (int)str.size();

	*strNum = str;
	return numLength;
}

// Generates a random number and a random place on screen.
void NumsOnScreen::numbersLottery(Board& board, const Point* head, int missionNumber, int* retNum, int* _x, int* _y)
{
	int x, y, num, numLength;
	string strNum;
	stringstream s;
	bool run = true;
	bool aroundOk;

	// Get a number
	num = generateNumber();

	strNum = num + '0';
	s << num;
	strNum = s.str();
	numLength = strNum.size();

	// Get the number location.
	while (run)
	{
		aroundOk = true;
		generateLocation(x, y, numLength);

		for (int i = 0; i < 2; i++)		//Check both snake1 and snake2
			for (int j = 0; j < numLength; j++)
				aroundOk &= checkAroundTheNumber(head[i], board, x + j, y);

		run = !aroundOk;	
	}

	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	// Sets the number on the board.
	for (int j = 0; j < numLength; j++)
	{
		board.setDigit(y, x + j, strNum.at(j));
		cout << board.getDigit(y, x + j);
	}

	*retNum = num;
	*_x = x;
	*_y = y;
}

int NumsOnScreen::generateNumber()
{
	int prob, num;

	prob = rand() % 3;
	switch (prob)
	{
	case 0:
		num = rand() % 26;
		break;
	case 1:
		num = (rand() % 56) + 26; // (81 - 26 + 1)
		break;
	case 2:
		num = (rand() % 88) + 82; // (169 - 82 + 1)
		break;
	}

	return num;
}

// Checks if the given location of the number is clear.
bool NumsOnScreen::checkAroundTheNumber(Point head, Board &board, int x, int y)
{
	//checks if there is an object in (x,y)
	if (!(board.isSpace(y, x)))
		return false;

	//checks if near to snake's head
	if ((head.getX() + 1 == x && head.getY() == y) || (head.getX() - 1 == x && head.getY() == y) ||
		(head.getX() == x && head.getY() + 1 == y) || (head.getX() == x && head.getY() - 1 == y))
		return false;

	//checks if near to a number
	if (isDigit(board.getDigit(y, x + 1)) || isDigit(board.getDigit(y, x - 1)) ||
		isDigit(board.getDigit(y + 1, x)) || isDigit(board.getDigit(y - 1, x)))
		return false;

	return true;
}

Point NumsOnScreen::getRandomNumFromArray()
{
	int i = rand() % howManyOnScreen;
	Point p;
	p = { number[i].x, number[i].y };
	return p;
}

int NumsOnScreen::getNumberByPosition(Point pos)
{
	for (int i = 0; i < howManyOnScreen; i++)
		if (number[i].x == pos.getX() && number[i].y == pos.getY())
			return number[i].num;
}

bool NumsOnScreen::isDigit(char c)
{
	if ((c >= '0' || c <= '9') && (int)c != -1)
		return true;
	return false;
}



#include "Missions.h"
#include "Point.h"
#include <sstream>
#include <math.h>

Missions::Mission7::Mission7()
{
		for (int i = 0; i < 2; i++)
		{
			oper[i].op = NULL;
			oper[i].level = NULL;
		}
		oper[2].op = '=';
		oper[2].level = 0;

		for (int i = 0; i < 4; i++)
			num[i] = NULL;
}

// Updates current mission string.
void Missions::setMission()
{
	x = (rand() % 10) + 2;
	do { y = rand() % x; } while (y == 0);  // The leftover for mission 5 

	switch (getCurrMission())
	{
	case 1:
		missionText = "Collect a prime number.";
		x = -1; // Not relevant.
		break;
	case 2:
		missionText = "Collect a number that is divisible by " + intToString(x) + ".";
		break;
	case 3:
		missionText = "Collect a number which is a multiple of " + intToString(x) + "."; 
		break;
	case 4:
		missionText = "Collect a number which is a power of a whole number.";
		x = -1; // Not relevant.
		break;
	case 5:
		missionText = "Collect a number which when divided by " + intToString(x) + " leaves a remainder of " + intToString(y) + "."; 
		break;
	case 6:
		missionText = "Collect the power of  " + intToString(x) + "."; 
		break;
	case 7:
		m.equationLottery();
		m.makeMissingNumber(missionText);
		x = -1; // Not relevant.
		break;
	};
}

// Chooses randomally the new mission.
void Missions::setCurrMission(int* activeMissions, int activeMissionCount)
{
	int newMission = currMission;

	// if there are more than one mission in the text file, choose it randomally,
	// otherwise, run the same mission.
	if(activeMissionCount > 1) 
		while (currMission == newMission)
			newMission = activeMissions[rand() % activeMissionCount];
	else
		newMission = activeMissions[rand() % activeMissionCount];

	currMission = newMission;
}

// Checks if its a good number for the current mission.
bool Missions::checkNumber(int num)
{
	switch (Missions::getCurrMission())
	{
	case 1:
		return mission1(num);
		break;
	case 2:
		return mission2(num);
		break;
	case 3:
		return mission3(num);
		break;
	case 4:
		return mission4(num);
		break;
	case 5:
		return mission5(num);
		break;
	case 6:
		return mission6(num);
		break;
	case 7:
		return mission7(num);
		break;
	}
}

// Prints new mission on screen.
void Missions::printMission()
{
	for (int i = 0; i < MAX_MISSION_LENGTH; i++)
	{
		gotoxy(i, 0);
		cout << " ";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW | FOREGROUND_INTENSITY);
	gotoxy(0, 0);
	cout << missionText;
	gotoxy(0, 1);
	cout << "                                                                                ";
}

void Missions::makeNewMission(int* activeMissions,int activeMissionCount)
{
	setCurrMission(activeMissions, activeMissionCount);
	setMission();
	printMission();
}

// Prime number.
bool Missions::mission1(int num)
{
	bool isPrime = true;

	if (num == 0)
		return false;

	for (int i = 2; i <= num / 2; ++i)
	{
		if (num % i == 0)
		{
			isPrime = false;
			break;
		}
	}

	if (isPrime)
		return true;
	else
		return false;
}

// Division by X.
bool Missions::mission2(int num) { return (num % x == 0 ? true : false); }

// Multiplication of X.
bool Missions::mission3(int num)
{
	if (num != 0 && num % x == 0)
		return true;

	return false;
}

// Power of a whole number.
bool Missions::mission4(int num)
{
	if (num == 1)
		return true;

	else
	{
		for (int i = 2; i < 14; i++)
			if (i*i == num)
				return true;

		return false;
	}
}

// Division by X with a remainder of Y.
bool Missions::mission5(int num) { return (num % x == y ? true : false); }

// The power of X.
bool Missions::mission6(int num) { return (num == pow(x,2) ? true : false); }

// Solving a mathematical equation.
bool Missions::mission7(int num) { return (num == m.getSolution() ? true : false); }

// Generates a random number and a random operator.
void Missions::Mission7::equationLottery()
{
	int random;
	bool goodEquation;

	do
	{
		// Get 4 numbers for the equation.
		for (int i = 0; i < 3; i++)
			Mission7::num[i] = rand() % 170;

		// Get 2 operands for the equation.
		for (int i = 0; i < 2; i++)
		{
			random = rand() % 4;
			Mission7::oper[i].op = Ops[random];
			checkAndSetOpLevel(oper[i].op, oper[i].level);
		}

		goodEquation = checkEquation();
	} while (!goodEquation);
}

// Checks priority of the mathematical operators.
void Missions::Mission7::checkAndSetOpLevel(char _op, int & level)
{
	if (_op == '+' || _op == '-')
		level = LEVEL1;

	else
		level = LEVEL2;
}

// Solve the equation and checks whether the result is in range.
bool Missions::Mission7::checkEquation()
{
	double sum = 0;

	if (oper[0].level < oper[1].level)
	{
		if (oper[1].op == '/' && num[2] == 0)
			return false;
		sum = calculator(num[1], oper[1].op, num[2]);
		sum = calculator(num[0], oper[0].op, sum);
	}

	else
	{
		if (oper[0].op == '/' && num[1] == 0)
			return false;
		sum = calculator(num[0], oper[0].op, num[1]);

		if (oper[1].op == '/' && sum == 0)
			return false;
		sum = calculator(sum, oper[1].op, num[2]);
	}


	if ((sum >= 0 && sum <= 169) && floor(sum) == sum)
	{
		num[3] = (int)sum;
		return true;
	}

	return false;
}

// calculator.
double Missions::Mission7::calculator(double num1, char op, double num2)
{
	switch (op)
	{
	case '+':
		return (num1 + num2);
		break;
	case '-':
		return (num1 - num2);
		break;
	case '*':
		return (num1 * num2);
		break;
	case '/':
		return (num1 / num2);
		break;
	}
}

// Generates a position for the number missing in the equation.
void Missions::Mission7::makeMissingNumber(string& text)
{
	int index = rand() % 4;
	string str = "Solve: ";
	solution = num[index];

	for (int i = 0, j = 0; i < 4; i++)
	{
		if (i == index)
			str += " _ ";
		else
			str += " " + intToString(num[i]) + " ";
		if (j < 3)
			str += oper[j++].op;
	}
	
	str += "?";
	text = str;
}

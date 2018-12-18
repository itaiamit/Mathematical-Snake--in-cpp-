#include "Utilities.h"

// Generate (x,y) accroding to screen limits.
void generateLocation(int& x, int& y, int numLength)
{
	y = (rand() % 21) + 3;
	switch (numLength)
	{
	case 1:
		x = (rand() % 78) + 1;
		break;
	case 2:
		x = (rand() % 77) + 1;
		break;
	case 3:
		x = (rand() % 76) + 1;
		break;
	}
}

Direction reverseDir(Direction dir)
{
	switch (dir)
	{
	case LEFT:
		return RIGHT;
		break;

	case RIGHT:
		return LEFT;
		break;

	case UP:
		return DOWN;
		break;

	case DOWN:
		return UP;
		break;
	}
}

// Converts number from int to string.
string intToString(int num)
{
	string str;
	stringstream s;

	str = num + '0';
	s << num;
	str = s.str();

	return str;
}

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

int* loadMissions(bool & run, int& missionCount)
{
	int activeMissions[NUM_OF_MISSIONS] = {};
	ifstream missionsFile("missions.txt");
	string str;
	int missionNum;
	bool existing = false;

	if (missionsFile.fail()) //check for file open failure
	{
		cout << "Error opening file." << endl;
		Sleep(300);
		run = false;
	}

	else if (isEmpty(missionsFile)) //check for an empty file
	{
		cout << "File is empty." << endl; 
		Sleep(300);
		run = false;
	}
	else
		while (!missionsFile.eof())
		{
			getline(missionsFile, str);
			missionNum = compareMission(str);
			if (missionNum == -1)
			{
				cout << "Error reading mission name." << endl;
				Sleep(300);
				run = false;
			}
			existing = isExistingMission(activeMissions, missionNum, missionCount);
			if (!existing)
			{
				missionCount++;
				activeMissions[missionCount - 1] = missionNum;
			}
		}

	missionsFile.close();
	return activeMissions;
}

bool isEmpty(ifstream& missionsFile)
{
	int current = missionsFile.tellg();
	missionsFile.seekg(0, missionsFile.end);
	bool empty = !missionsFile.tellg(); // true if empty file
	missionsFile.seekg(current, missionsFile.beg); //restore stream position

	return empty;
}



int compareMission(string str)
{
	for (int i = 0; i < NUM_OF_MISSIONS; i++)
		if (str.compare(allMissions[i]) == 0)
			return (i + 1);

	return -1; // Illegal mission name.
}

bool isExistingMission(int * activeMissions, int missionNum, int missionCount)
{
	for (int i = 0; i < missionCount; i++)
		if (missionNum == activeMissions[i])
			return true;

	return false;
}

void clrscr() { system("cls"); }
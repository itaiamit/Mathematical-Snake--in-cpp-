#ifndef _MISSIONS_H_
#define _MISSIONS_H_
#include "Point.h"
#include "Board.h"
#include "Numbers.h"
#include <Windows.h>
#include "Colors.h"
#include <string>

class NumsOnScreen;
class Board;
enum {MAX_MISSION_LENGTH = 70};
enum { LEVEL1 = 1, LEVEL2 };

struct Operator
{
	int level;
	char op;
};

class Missions
{
	int x, y; //The random part of the mission.
	class Mission7
	{
		char Ops[4] = { '+', '-', '*', '/'};
		int num[4] = {};
		Operator oper[3];
		int solution;
		friend class Missions;

	public:
		Mission7();
		int getSolution() { return solution; }
		void equationLottery();
		void checkAndSetOpLevel(char _op, int& level);
		bool checkEquation();
		double calculator(double num1, char op, double num2);
		void makeMissingNumber(string& text);
	};
	int currMission = 1;
	string missionText;
	Mission7 m;

public:
	Missions(int _missionNum = 1)
	{
		currMission = _missionNum;
		setMission();
	}
	void setMission();
	int getCurrMission() { return currMission; }
	void setCurrMission(int* activeMissions, int activeMissionCount);
	string getMissionString() { return missionText; }
	void setMissionText(string str) { missionText.assign(str); }
	void updateCurrMission() { currMission++; }
	bool checkNumber(int num);
	void printMission();
	void makeNewMission(int* activeMissions, int activeMissionCount);
	bool mission1(int num);
	bool mission2(int num);
	bool mission3(int num);
	bool mission4(int num);
	bool mission5(int num);
	bool mission6(int num);
	bool mission7(int num);
};

#endif // !_MISSIONS_H_
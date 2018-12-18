#ifndef _UTILIITIES_H_
#define _UTILIITIES_H_

#include <iostream>
#include <sstream>
#include <windows.h>
#include <process.h>
#include <fstream>
#include <time.h>
#include "Direction.h"

using namespace std;

enum {HEAD = 0, NUM_OF_MISSIONS = 7 };
const string BLANK_ROW = "                                                                               ";
const string allMissions[] = {
	"Collect a prime number.",
	"Collect a number that is divisible by X.",
	"Collect a number which is a multiple of X.",
	"Collect a number which is a power of a whole number.",
	"Collect a number which when divided by X leaves a remainder of Y.",
	"Collect the power of X.",
	"num1 op1 num2 op2 num3 = num4"
};
void generateLocation(int & x, int & y, int numLength);
Direction reverseDir(Direction dir);
string intToString(int num);
void gotoxy(int, int);
int* loadMissions(bool& run, int& missionCount);
bool isEmpty(ifstream& missionsFile);
int compareMission(string str);
bool isExistingMission(int* activeMissions, int missionNum,int  missionCount);
void clrscr();

#endif